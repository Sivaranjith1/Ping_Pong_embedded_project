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

enum cal_range {MIN, MAX};
enum cal_channel {JOYSTICK_X, JOYSTICK_Y, SLIDER_R, SLIDER_L};

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
    float range_min;
    float range_idle;
    float range_max;
} pos_calibrate_t;

void pos_set_offset_calibration(enum cal_channel);

void pos_set_range_calibration(enum cal_channel, enum cal_range);

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

/**
 * @brief Get the x and y position of the joystick and the slider values. The output will use the last calibration
 * 
 * @return pos_t the x and y value of the joystick, and slider_r and slider_l
 */
pos_t pos_read(void);


#endif /* ADC_H_ */
