#include "sam.h"
#include "motor.h"
#include "../DACC/dacc.h"
#include "pid.h"

#define MOTOR_ENCODER_DATA_SHIFT 1
#define MOTOR_ENCODER_ENCODER_MAX_VALUE 65535

static uint8_t motor_read_encoder_data();

typedef struct {
    float max_value;
    float min_value;
} motor_encoder_calibration_t;

//calibration struct for the encoder output of the motor
static motor_encoder_calibration_t motor_encoder_calibration = {
    .max_value = 6600,
    .min_value = 0
};


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
    
    PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PIOC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER0 |= 1 << (ID_PIOC); //enable PIOC in PMC

    // For encoder data lines
    PIOC->PIO_PER = 0xFF << MOTOR_ENCODER_DATA_SHIFT;
}

void motor_set_speed(float speed){
    //printf("Speed %d\n\r", (uint8_t)speed);
    float dac_input = 0;
    if(speed <= 0){
        if(speed <= -1) {
            dac_input = 1;
        } else {
            dac_input = speed*(-1);
        }

        motor_set_direction(MOTOR_LEFT);
    } else{
        if(speed >= 1){
            dac_input = 1;
        } else {
            dac_input = speed;
        }
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

int16_t motor_read_encoder(void){
    
    PIOD->PIO_CODR |= PIO_CODR_P0; // Setting !OE low; enable output
    PIOD->PIO_CODR |= PIO_CODR_P2; // Set sel low; get higher bytes

    for (uint32_t i; i < 20*84; ++i) __NOP();

    uint8_t encoder_high_byte = motor_read_encoder_data();

    PIOD->PIO_SODR |= PIO_SODR_P2; // Set sel high; get lower bytes

    for (uint32_t i; i < 20*84; ++i) __NOP();   

    uint8_t encoder_low_byte = motor_read_encoder_data();

    PIOD->PIO_SODR |= PIO_SODR_P0; // Setting !OE high; enable output
    int16_t encoder_raw_data = (-1)*(int16_t)(encoder_high_byte << 8 | encoder_low_byte); //positive direction is to the right

    return encoder_raw_data;
}

void motor_reset_encoder(){
    PIOD->PIO_CODR |= PIO_CODR_P1; // pull !RST LOW
    for (uint32_t i; i < 20; ++i) __NOP();
    PIOD->PIO_SODR |= PIO_SODR_P1; // pull !RST High
}

float motor_get_position(){
    //positive direction to the right
    int16_t encoder_raw_data = motor_read_encoder();

    float motor_pos = ((float)encoder_raw_data - motor_encoder_calibration.min_value)/(motor_encoder_calibration.max_value - motor_encoder_calibration.min_value);

    //clamp the output
    if(motor_pos < 0) return 0;
    if(motor_pos > 1) return 1;
    return motor_pos;
}

void motor_position_set_max_value(){
    int16_t encoder_raw_data = motor_read_encoder();

    motor_encoder_calibration.max_value = encoder_raw_data;
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