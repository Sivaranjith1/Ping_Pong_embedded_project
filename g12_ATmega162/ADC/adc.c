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


uint8_t adc_read_polled(uint8_t channel){
	xmem_write(0x08 | (channel & 0x1) << 7 | (channel & 0x2) << 5, ADC_BASE_ADDRESS); //send a command to read the desired channel

	while(!gpio_pin_read(PINE0, PINE)); //wait for the adc stop being busy

    return xmem_read(ADC_BASE_ADDRESS); //read only one byte of data
}
