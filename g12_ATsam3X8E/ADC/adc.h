/**
 * @file adc.h
 * @author Ask Øren
 * @brief Driver for reading internal ADC values from ATSAM3X8E
 * @version 0.1
 * @date 2021-10-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

void adc_init(void);

void adc_start_conversion(void);

void adc_stop_conversion(void);

float adc_get_data(uint8_t channel);

float adc_get_ema_filtered_data(uint8_t channel, float alpha);

void ADC_Handler(void);

#endif