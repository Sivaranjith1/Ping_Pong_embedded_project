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
#include <avr/interrupt.h>

#if ADC_DEBUG
#define ADC_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define ADC_DEBUG_PRINT(...)
#endif // ADC_DEBUG

// raw data saved in the interrupt
static uint8_t adc_raw_data[4] = {0};

/**
 * @brief 
 * 
 */

pos_calibrate_t joystick_x_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xFF
};

pos_calibrate_t joystick_y_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xFF
};

pos_calibrate_t slider_l_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xff
};

pos_calibrate_t slider_r_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xff
};

void adc_start_conversion(){
	xmem_write(0, ADC_BASE_ADDRESS); //send a command to read all channels
}

uint8_t adc_get_channel_data(uint8_t channel){
	return adc_raw_data[channel];
}

void pos_set_offset_calibration(enum cal_channel channel){
	switch (channel)
	{
	case SLIDER_L:
		break;
	case SLIDER_R:
		break;
	case JOYSTICK_Y:
	{
		joystick_y_calibration.range_idle = ((float)adc_get_channel_data((uint8_t)channel));
		break;
	}
	case JOYSTICK_X:{
		joystick_x_calibration.range_idle = ((float)adc_get_channel_data((uint8_t)channel));
		break;
	}
	default:
		break;
	}
}

void pos_set_range_calibration(enum cal_channel channel, enum cal_range range){
	switch (channel)
	{
	case SLIDER_L:
		if(range == MIN){
			slider_l_calibration.range_min = adc_get_channel_data(channel);
		}
		else if(range == MAX){
			slider_l_calibration.range_max = adc_get_channel_data(channel);
		}
		break;
	case SLIDER_R:
		if(range == MIN){
			slider_r_calibration.range_min = adc_get_channel_data(channel);
		}
		else if(range == MAX){
			slider_r_calibration.range_max = adc_get_channel_data(channel);
		}
		break;
	case JOYSTICK_Y:{
		if(range == MIN){
			joystick_y_calibration.range_min = adc_get_channel_data(channel);
			printf("Y MIN: %i\n\r", (int)(joystick_y_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_y_calibration.range_max = adc_get_channel_data(channel);
			printf("Y MAX: %i\n\r", (int)(joystick_y_calibration.range_max*100));
		}
		break;
	}
	case JOYSTICK_X:{
		if(range == MIN){
			joystick_x_calibration.range_min = adc_get_channel_data(channel);
			printf("X MIN: %i\n\r", (int)(joystick_x_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_x_calibration.range_max = adc_get_channel_data(channel);
			printf("X MAX: %i\n\r", (int)(joystick_x_calibration.range_max*100));
		}
		break;
	}
	default:
		break;
	}
}

pos_t pos_read(void){
	float slider_r 	= (float)adc_get_channel_data((uint8_t)SLIDER_L);
	float slider_l 	= (float)adc_get_channel_data((uint8_t)SLIDER_R);
	float pos_y		= (float)adc_get_channel_data((uint8_t)JOYSTICK_Y);
	float pos_x 	= (float)adc_get_channel_data((uint8_t)JOYSTICK_X);

	//printf("pos_y : %d\n\r", (int)(pos_y));

	pos_t output;

	if (pos_x >= joystick_x_calibration.range_idle){
		output.pos_x = 0.5*(pos_x - (float)joystick_x_calibration.range_idle)/((float)joystick_x_calibration.range_max - (float)joystick_x_calibration.range_idle) + 0.5;
	}
	else if(pos_x < joystick_x_calibration.range_idle){
		output.pos_x = 0.5*(pos_x - (float)joystick_x_calibration.range_min)/((float)joystick_x_calibration.range_idle - (float)joystick_x_calibration.range_min);
	}
	if (pos_y >= joystick_y_calibration.range_idle){
		output.pos_y = 0.5*(pos_y - (float)joystick_y_calibration.range_idle)/((float)joystick_y_calibration.range_max - (float)joystick_y_calibration.range_idle) + 0.5;
	}
	else if(pos_y < joystick_y_calibration.range_idle){
		output.pos_y = 0.5*(pos_y - (float)joystick_y_calibration.range_min)/((float)joystick_y_calibration.range_idle - (float)joystick_y_calibration.range_min);
	}
	
	//output.slider_l = (slider_l - slider_l_calibration.offset) / (slider_l_calibration.range_max - slider_l_calibration.range_min) - 1;
	//output.slider_r = (slider_r - slider_r_calibration.offset) / (slider_r_calibration.range_max - slider_r_calibration.range_min) - 1;

	return output;
}

/**
 * @brief Construct a new ISR object for handling the event of ADC finishing conversion
 * 
 */
ISR(INT2_vect){
	ADC_DEBUG_PRINT("Hello from INT2\n\r");

	// saving raw_data in array
	for (uint8_t i = 0; i < 4; i++)
	{
		adc_raw_data[i] = xmem_read(ADC_BASE_ADDRESS);
	}
	
	printf("Channel 2; %i	", adc_raw_data[2]);
	printf("Channel 3; %i	", adc_raw_data[3]);
	printf("Channel 0; %i	", adc_raw_data[0]);
	printf("Channel 1; %i\n\r", adc_raw_data[1]);
	
	GIFR = (1 << INTF2);  // clear flags
}
