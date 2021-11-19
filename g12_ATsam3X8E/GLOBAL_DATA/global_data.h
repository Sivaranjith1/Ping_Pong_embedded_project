/**
 * @file global_data.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Functions for copying data into a global place. This can be done to pass data between pointers. 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GLOBAL_DATA_H_
#define GLOBAL_DATA_H_

#include "../CAN/can_messages.h"

/**
 * @brief Set the global value with the joystick value from can
 * 
 * @param joystick_data the value to copy to the global state
 */
void global_data_set_joystick(can_joystick_pos_t* joystick_data);

/**
 * @brief Get the global value with the joystick values from can
 * 
 * @param joystick_data the struct to copy values to
 */
void global_data_get_joystick(can_joystick_pos_t* joystick_data);

#endif