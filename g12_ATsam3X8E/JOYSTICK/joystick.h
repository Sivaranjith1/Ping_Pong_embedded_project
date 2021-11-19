/**
 * @file joystick.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Driver for actions based on the joystick values over CAN from Node 1
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include <float.h>
#include "../CAN/can_messages.h"

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
} joystick_t;

/**
 * @brief Struct used for calibration of the joystick, used for mapping the joystick input from 0 - 100
 * 
 */
typedef struct
{
    float range_min;
    float range_idle;
    float range_max;
} joystick_calibrate_t;

/**
 * @brief Stores joystick calibration data to FLASH memory
 * 
 */
void joystick_store_calibration(void);

/**
 * @brief Initialises the button associated with extending the solenoid
 * 
 */
void joystick_init(void);

/**
 * @brief Gets the offset values for idle position of the joystick and 
 * stores them in the joystick calibrate structs
 * 
 * @param data data recieved from CAN
 * @param cal_channel JOYSTICK_X or JOYSTICK_Y
 */
void joystick_set_offset_calibration(enum cal_channel, char* data);

/**
 * @brief Sets min and maximum limits for the joystick
 * 
 * @param data Joystick data from the CAN bus
 * @param cal_channel JOYSTICK_X or JOYSTICK_Y
 * @param cal_range minimum value or maximum value
 */
void joystick_set_range_calibration(enum cal_channel, enum cal_range, char* data);

/**
 * @brief Converts the joystick data recieved from the CAN bus to floats using
 * the offest and range from the calibrations
 * 
 * @param data recieved from the CAN bus
 * @return can_joystick_pos_t 
 */
can_joystick_pos_t joystick_convert(char* data);


/**
 * @brief Extends the solenoid
 * 
 */
void joystick_pulse_on(void);

/**
 * @brief Counts how long the solenoid has been extended for
 * after a set amount of time it pulls the solenoid back in, creating a pulse of controllable length
 */
void joystick_pulse_off(void);

#endif //JOYSTICK_H