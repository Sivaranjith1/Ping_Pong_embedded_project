/**
 * @file adc.h
 * @author Sivaranjith Sivarasa
 * @brief Driver for reading from adc. This is given that the adc is setup as xmem, see xmem.h
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

enum cal_range {MIN, MAX};
enum cal_channel {JOYSTICK_X, JOYSTICK_Y, SLIDER_R, SLIDER_L};

/**
 * @brief Start conversion of all data channels. When the conversion is finish a isr will be called and data will be updated. 
 * 
 */
void adc_start_conversion();

/**
 * @brief Get adc data from the last conversion. 
 * 
 * @param channel the channel to get the data from
 * @return uint8_t the data from the chosen channel
 */
uint8_t adc_get_channel_data(uint8_t channel);

#endif /* ADC_H_ */
