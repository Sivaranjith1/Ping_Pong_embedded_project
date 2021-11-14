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
#include "../CAN/can.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#if ADC_DEBUG
#define ADC_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define ADC_DEBUG_PRINT(...)
#endif // ADC_DEBUG

// raw data saved in the interrupt
static uint8_t adc_raw_data[4] = {0};
static uint8_t adc_conversion_finished = 1;

void adc_start_conversion(){
	if(!adc_conversion_finished) return;
	xmem_write(0, ADC_BASE_ADDRESS); //send a command to read all channels
	adc_conversion_finished = 0;
}

uint8_t adc_get_channel_data(uint8_t channel){
	return adc_raw_data[channel];
}

/**
 * @brief Construct a new ISR object for handling the event of ADC finishing conversion
 * 
 */
ISR(INT2_vect){
	cli();
	ADC_DEBUG_PRINT("Hello from INT2\n\r");

	// saving raw_data in array
	for (uint8_t i = 0; i < 4; i++)
	{
		adc_raw_data[i] = xmem_read(ADC_BASE_ADDRESS);
	}
	adc_conversion_finished = 1;
	GIFR = (1 << INTF2);  // clear flags
	sei();
}
