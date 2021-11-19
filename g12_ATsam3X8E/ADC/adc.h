/**
 * @file adc.h
 * @author Ask Øren, Steffen Folåasen, Sivaranjith Sivarasa
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

/**
 * @brief Initialize ADC channel 0 with timer interrupts
 * 
 */
void adc_init(void);

/**
 * @brief Start converting the analog signals to digital
 * 
 */
void adc_start_conversion(void);

/**
 * @brief Stop the convertion
 * 
 */
void adc_stop_conversion(void);

/**
 * @brief Get the latest adc readout
 * 
 * @param channel the channel to read from
 * @return float voltage in V
 */
uint16_t adc_get_data(uint8_t channel);


/**
 * @brief Helper function, ema filtering data, this should be used instead of adc_get_data for best results
 * @param channel the channel to do ema filtering on 
 * @param alpha weighting for measurement. Should be between 0 and 1. A higher number means a higher weighting of the measurement
 * @return uint16_t the filtered values
 */
uint16_t adc_get_ema_filtered_data(uint8_t channel, float alpha);

/**
 * @brief The interrupt handler for the convertion is finished
 * 
 */
void ADC_Handler(void);

#endif