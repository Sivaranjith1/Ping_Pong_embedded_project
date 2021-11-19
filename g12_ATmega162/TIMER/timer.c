#include "timer.h"
#include <avr/interrupt.h>
#include "../system_config.h"
#include "../FSM/fsm.h"

// 20 Hz
#define COMP_1A_REG  3840

// 10 Hz
#define COMP_3A_REG 1920

#if TIMER1_DEBUG
#define TIMER1_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TIMER1_DEBUG_PRINT(...)
#endif // TIMER1_DEBUG

#if TIMER3_DEBUG
#define TIMER3_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TIMER3_DEBUG_PRINT(...)
#endif // TIMER3_DEBUG

static uint8_t play = 0; //if the timer variable should count
static uint8_t timer = 0; //internal variable to count to 1 sek
static uint16_t curr_time = 0; //the time since timer start

void timer_init(){
    // Setup for timer counter 1 and 3
    TCCR1A |= (1 << COM1A1); // compare mode for timer 1
    TCCR3A |= (1 << COM3A1); // compare mode for timer 3
    TCCR1B |= (1 << WGM12) | (1 << CS11) | (1 << CS10); // CTC mode on, clk = MCK/64
    TCCR3B |= (1 << WGM32) | (1 << CS32); // CTC mode on, clk = MCK/256

    // Setting compare to match desired value
    OCR1A = COMP_1A_REG;
    OCR3A = COMP_3A_REG;
            
    // Timer interrupt enable for solenoid button and play time
    TIMSK = (1 << OCIE1A);
    ETIMSK = (1 << OCIE3A);
}

void timer_start(){
    // start counting timer
    timer = 0;
    curr_time = 0;
    play = 1;
}

void timer_stop(){
    // stop counting timer
    play = 0;
}

uint8_t timer_get_play(){
    return play;
}

uint16_t timer_get_time(){
    uint16_t current_time = curr_time;
    return current_time;
}

ISR(TIMER1_COMPA_vect){
    TIMER1_DEBUG_PRINT("Timer 1 interrupt\n\r");
    fsm_add_event(FSM_EV_TIMER_1);
    fsm_add_event(FSM_EV_STATE_TIMER_1);
}

ISR(TIMER3_COMPA_vect){
    TIMER3_DEBUG_PRINT("Timer 3 interrupt\n\r");
    timer++;
    if(play && timer == 10){
        curr_time++;
        timer = 0;
    }
    fsm_add_event(FSM_EV_TIMER_3);
    fsm_add_event(FSM_EV_STATE_TIMER_3);
}
