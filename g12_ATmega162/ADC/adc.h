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
#include <float.h>

/**
 * @brief position of the joysticks and sliders, the values will be between -1 and 1.
 * 
 */
typedef struct
{
    float pos_x;
    float pos_y;
    float slider_l;
    float slider_r;
} pos_t;

typedef struct
{
    float offset;
    float range;
} pos_calibrate_t;


/**
 * @brief Will read a given channel from the adc. It will be a busy wait and pulling of the busy signal
 * 
 * @param channel the channel to read. 0 to 3
 * @return uint8_t return the value from the adc
 */
uint8_t adc_read_polled(uint8_t channel);

/**
 * @brief Get the x and y position of the joystick and the slider values. The output will use the last calibration
 * 
 * @return pos_t the x and y value of the joystick, and slider_r and slider_l
 */
pos_t pos_read(void);


#endif /* ADC_H_ */
