#include "sam.h"
#include "motor.h"
#include "../DACC/dacc.h"

#define MOTOR_ENCODER_DATA_SHIFT 1

static uint8_t motor_read_encoder_data();

void motor_init(){
	PIOD->PIO_PER = PIO_PER_P1; // For !Reset
	PIOD->PIO_PER = PIO_PER_P9; // For EN
	PIOD->PIO_PER = PIO_PER_P10; // For DIR
    PIOD->PIO_OER = PIO_OER_P1;
    PIOD->PIO_OER = PIO_OER_P9;
    PIOD->PIO_OER = PIO_OER_P10;

	PIOD->PIO_PER = PIO_PER_P0; // For !OE
	PIOD->PIO_PER = PIO_PER_P2; // For SEL
	PIOD->PIO_OER = PIO_OER_P0;
	PIOD->PIO_OER = PIO_OER_P2;

    PIOD->PIO_SODR |= PIO_SODR_P1;
    PIOD->PIO_SODR |= PIO_SODR_P9;
    
    PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (PIC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_ADC - 32); //enable ADC in PMC

    // For encoder data lines
    PIOC->PIO_PER = 0xFF << MOTOR_ENCODER_DATA_SHIFT;
}

void motor_set_speed(float speed){
    //printf("Speed %d\n\r", (uint8_t)speed);
    float dac_input = 0;
    if(speed <= 0.5){
        dac_input = 1 - speed*2;
        motor_set_direction(MOTOR_LEFT);
    } else {
        dac_input = (speed - 0.5)*2;
        motor_set_direction(MOTOR_RIGHT);
    }
    dacc_convert(dac_input);
}

void motor_set_direction(motor_direction_t direction){
    if(direction == MOTOR_LEFT){
        PIOD->PIO_CODR |= PIO_CODR_P10;
    } else{
        PIOD->PIO_SODR |= PIO_SODR_P10;
    }
}

uint16_t motor_read_encoder(void){
    
    PIOD->PIO_CODR |= PIO_CODR_P0; // Setting !OE low; enable output
    PIOD->PIO_CODR |= PIO_CODR_P2; // Set sel low; get higher bytes

    for (uint32_t i; i < 20*84; ++i) __NOP();

    uint8_t encoder_high_byte = motor_read_encoder_data();

    PIOD->PIO_SODR |= PIO_SODR_P2; // Set sel high; get lower bytes

    for (uint32_t i; i < 20*84; ++i) __NOP();

    uint8_t encoder_low_byte = motor_read_encoder_data();

    PIOD->PIO_SODR |= PIO_SODR_P0; // Setting !OE low; enable output
    return (encoder_high_byte << 8 | encoder_low_byte);
}

void motor_reset_encoder(){
    PIOD->PIO_CODR |= PIO_CODR_P1; // pull !RST LOW
    for (uint32_t i; i < 20; ++i) __NOP();
    PIOD->PIO_SODR |= PIO_SODR_P1; // pull !RST High
}

/**
 * @brief Reads a byte from the encoder data lines. The sel and OE line has to be sat before calling this function
 * 
 * @return uint8_t The data byte
 */
static uint8_t motor_read_encoder_data(){
    // pin 33 to 40 is connected with DO0 to DO7 respectivly
    // pin 33 to 40 is mapped to PC1 to PC8 respectively
    return (PIOC->PIO_PDSR >> MOTOR_ENCODER_DATA_SHIFT) & 0xFF;
}