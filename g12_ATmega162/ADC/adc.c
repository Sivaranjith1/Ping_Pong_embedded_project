/**
 * @file adc.c
 * @author Sivaranjith Sivarasa
 * @brief Driver for reading from adc. This is given that the adc is setup as xmem, see xmem.h
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "adc.h"
#include "../system_config.h"

#include <avr/io.h>

/**
 * @brief Default calibration values for joystick and sliders
 * 
 */
pos_calibrate_t joystick_x_calibration = {
	.offset = 0,
	.range = 0xFF
};

pos_calibrate_t joystick_y_calibration = {
	.offset = 0,
	.range = 0xFF
};

pos_calibrate_t slider_l_calibration = {
	.offset = 0,
	.range = 0xff
};

pos_calibrate_t slider_r_calibration = {
	.offset = 0,
	.range = 0xff
};


uint8_t adc_read_polled(uint8_t channel){
	xmem_write(channel | 1 << 7, ADC_BASE_ADDRESS); //send a command to read the desired channel

	while(!gpio_pin_read(PINE0, PINE)); //wait for the adc stop being busy

    return xmem_read(ADC_BASE_ADDRESS); //read only one byte of data
}

pos_t pos_read(void){
	uint8_t slider_r 	= adc_read_polled(0);
	uint8_t slider_l 	= adc_read_polled(1);
	uint8_t pos_y		= adc_read_polled(2);
	uint8_t pos_x 		= adc_read_polled(3);

	pos_t output = {
		// Calculation for the calibrated sensor. The output should be between -1 and 1. 
		// One starts by removing the offset, then dividing with range to get a scaled value between 0 and 1.
		// Multipling by 2 and subtracting 1 will transform a value between 0 and 1 to a value between -1 and 1
		.pos_x = 2 * (pos_x - joystick_x_calibration.offset) / joystick_x_calibration.range - 1,
		.pos_y = 2 * (pos_y - joystick_y_calibration.offset) / joystick_y_calibration.range - 1,
		.slider_l = 2 * (slider_l - slider_l_calibration.offset) / slider_l_calibration.range - 1,
		.slider_r = 2 * (slider_r - slider_r_calibration.offset) / slider_r_calibration.range - 1
	};

	return output;
}