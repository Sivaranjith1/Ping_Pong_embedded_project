#include "timer.h"
#include <avr/interrupt.h>
#include "../gpio/gpio.h"
#include "../ADC/adc.h"
#include "../ADC/joystick.h"
#include "../OLED/oled.h"

// 50 Hz
#define COMP_A_REG  7680 // 12288

#if TIMER1_DEBUG
#define TIMER1_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define TIMER1_DEBUG_PRINT(...)
#endif // TIMER1_DEBUG

void timer_init(){
    // Setup for timer counter 1
    TCCR1A = (1 << COM1A1); // compare mode for timer 1
    TCCR1B = (1 << CS11) | (1 << CS10) | (1 << WGM12); // clk = MCLK/64, CTC mode on

    // Setting compare to match desired value
    OCR1A = COMP_A_REG;

    // Timer interrupt enable compare A
    TIMSK = (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect){
    TIMER1_DEBUG_PRINT("Timer 1 interrupt\n\r");
    //joystick_can_transmit_pos();
    adc_start_conversion();
    //joystick_poll_buttons();
    //oled_refresh();
}
