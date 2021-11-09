/**
 * @file main.c
 * @author Ask Øren, Steffen Folåsen 
 * @brief The main application of the ATSAME3X8E for this project
 * @version 1.0 
 * @date 2021-10-05
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "sam.h"
#include "system_config.h"
#include "CAN/can_controller.h"
#include "CAN/can_interrupt.h"
#include "UART/uart.h"
#include "UART/printf-stdarg.h"
#include "PWM/pwm.h"
#include "ADC/adc.h"
#include "ADC/goal_handler.h"
#include "TIMER/timer.h"
#include "DACC/dacc.h"
#include "MOTOR/motor.h"


/**
 * @brief Run all init functions for different peripherals in one function
 * 
 */
void init(void){
    SystemInit();
    configure_uart();
    can_init_def_tx_rx_mb(CAN_BR_VALUES);
    pwm_init();
    adc_init();
    timer_init();
    dacc_init();
    motor_init();
}

/**
 * @brief The main function with the infinite while loop 
 * 
 */
int main(void)
{
    /* Initialize the SAM system */

    init();
    //pwm_update_duty_cycle(50, 6);
	printf("\n\rAtsame starting ...\n\r");
    
    WDT->WDT_MR = WDT_MR_WDDIS;
    while (1) 
    {
        if(goal_check_for_goal()){
            printf("GOOOOOOOAL %d \n\r", goal_get_goals());
            for (uint16_t i = 0; i < 10000; i++);
        }
        //printf("Encoder data: %d \n\r", motor_read_encoder());
        /*
        for (uint32_t i = 0; i < 100000; i++);
        float data = adc_get_data(0);
        printf("Here is some data bitches %d \n\r", (uint32_t) data * 1000);
        printf("Bert, convert: %d \n\r", (uint32_t)adc_get_ema_filtered_data(0, 0.6) * 1000);
        */
    }
    return 0;
}
