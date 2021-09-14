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

uint8_t adc_read_polled(uint8_t channel);



#endif /* ADC_H_ */
