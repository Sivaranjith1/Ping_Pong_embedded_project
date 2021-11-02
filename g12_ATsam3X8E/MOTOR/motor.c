#include "sam.h"
#include "motor.h"
#include "../DACC/dacc.h"

void motor_init(){
	PIOD->PIO_PER = PIO_PER_P9; // For EN
	PIOD->PIO_PER = PIO_PER_P10; // For DIR
    PIOD->PIO_OER = PIO_OER_P9;
    PIOD->PIO_OER = PIO_OER_P10;

	PIOD->PIO_PER = PIO_PER_P0; // For !OE
	PIOD->PIO_PER = PIO_PER_P2; // For SEL
	PIOD->PIO_OER = PIO_OER_P0;
	PIOD->PIO_OER = PIO_OER_P2;

    PIOD->PIO_SODR |= PIO_SODR_P9;
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

uint32_t motor_read_encoder(void){
    PIOD->PIO_CODR |= PIO_CODR_P0;
    PIOD->PIO_CODR |= PIO_CODR_P2;

    for (uint32_t i; i < 20*84; ++i) __NOP();


}