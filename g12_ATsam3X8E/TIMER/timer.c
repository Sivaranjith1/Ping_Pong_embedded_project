#include "timer.h"
#include "sam.h"
#include "../ADC/adc.h"
#include "../ADC/goal_handler.h"
#include "../GLOBAL_DATA/global_data.h"
#include "../JOYSTICK/joystick.h"
#include "../PWM/pwm.h"
#include "../MOTOR/motor.h"
#include "../MOTOR/pid.h"
#include "../DACC/dacc.h"
#include "../CAN/can_controller.h"
#include "../system_config.h"

#define RC_COMP_TC0 840000 // 50 Hz
#define RC_COMP_TC1 52500 // 50 Hz
#define RC_COMP_TC2 328125 // 2 Hz

#if TC0_DEBUG
#include "../UART/printf-stdarg.h"
#define TC0_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TC0_DEBUG_PRINT(...)
#endif // TC0_DEBUG

#if TC1_DEBUG
#include "../UART/printf-stdarg.h"
#define TC1_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TC1_DEBUG_PRINT(...)
#endif // TC1_DEBUG

#if TC2_DEBUG
#include "../UART/printf-stdarg.h"
#define TC2_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TC2_DEBUG_PRINT(...)
#endif // TC2_DEBUG

void timer_init(void){
    // Setup for TC0
    PIOB->PIO_PDR |= PIO_PDR_P26; 
    PIOB->PIO_ABSR |= PIO_ABSR_P26; 

    // Setup for TC1
    PIOA->PIO_PDR |= PIO_PDR_P23; 
    PIOA->PIO_ABSR |= PIO_ABSR_P23;

    // Setup for TC2 
    PIOD->PIO_PDR |= PIO_PDR_P9;
    PIOD->PIO_ABSR |= PIO_ABSR_P9;

    // Enable clocks in PMC
    PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_TC0 << PMC_PCR_PID_Pos) | (ID_TC1 << PMC_PCR_PID_Pos) | (ID_TC2 << PMC_PCR_PID_Pos); 
    PMC->PMC_PCER0 |= (1 << ID_TC0) | (1 << ID_TC1) | (1 << ID_TC2); 

    // Disables WP
    TC0->TC_WPMR = (0x54494D << 8);
    TC1->TC_WPMR = (0x54494D << 8);
    TC2->TC_WPMR = (0x54494D << 8);

    // Sets clock to be MCK/2, MCK/32 and MCK/128 respectively
    TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1;
    TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK3;
    TC0->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4;
 
    // Sets the compare-value to be used in interrupts
    TC0->TC_CHANNEL[0].TC_RC = RC_COMP_TC0;
    TC0->TC_CHANNEL[1].TC_RC = RC_COMP_TC1;
    TC0->TC_CHANNEL[2].TC_RC = RC_COMP_TC2;

    // Enables and starts clock, also enables compare with RC
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG | TC_CMR_CPCTRG;
    TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG | TC_CMR_CPCTRG;
    TC0->TC_CHANNEL[2].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG | TC_CMR_CPCTRG;

    // Enable interrupt requests, compare with the RC-value
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
    TC0->TC_CHANNEL[1].TC_IER = TC_IER_CPCS;
    TC0->TC_CHANNEL[2].TC_IER = TC_IER_CPCS;

    // Interrupt enable
    NVIC_EnableIRQ(TC0_IRQn);
    NVIC_EnableIRQ(TC1_IRQn);
    NVIC_EnableIRQ(TC2_IRQn);
}

void TC0_Handler(void){
    TC0_DEBUG_PRINT("ADC TIMER TRIGGER\n\r");
    uint8_t status = TC0->TC_CHANNEL[0].TC_SR; // clear interrupt flag 
    adc_start_conversion();
    joystick_pulse_off();
    TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG; // restart timer
    NVIC_ClearPendingIRQ(TC0_IRQn);
}

void TC1_Handler(void){
    //TC1_DEBUG_PRINT("PID TIMER TRIGGER\n\r");
    uint8_t status = TC0->TC_CHANNEL[1].TC_SR; // clear interrupt flag

    can_joystick_pos_t joystick_data;
    global_data_get_joystick(&joystick_data);

    pwm_update_from_joystick(joystick_data.x_pos);
    motor_set_speed(pid_vel_controller(joystick_data.y_pos, motor_get_position()));

    TC1_DEBUG_PRINT("joystick from timer %d\n\r", (uint8_t)(joystick_data.y_pos*100));

    TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG; // restart timer
    NVIC_ClearPendingIRQ(TC1_IRQn);
}

void TC2_Handler(void){
    TC2_DEBUG_PRINT("SCORE TIMER INTERRUPT \n\r");
    uint8_t status = TC0->TC_CHANNEL[2].TC_SR; // clear interrupt flag

    if(goal_check_for_goal()){
        CAN_MESSAGE goal;
        goal.id = CAN_GOAL_SCORED_ID;
        goal.data_length = 1;
        goal.data.char_array[0] = goal_get_goals();
        can_send(&goal, goal.id);
    }
    TC0->TC_CHANNEL[2].TC_CCR = TC_CCR_SWTRG; // restart timer
    NVIC_ClearPendingIRQ(TC2_IRQn);
}