/**
 * @file joystick.h
 * @author Steffen Folåsen, Ask Øren, Sivaranjith Sivarasa
 * @brief Read the joystick value from the ADC. Depends on the adc.h
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../CAN/can.h"

/**
 * @brief Enable pins for reading joystick buttons 
 * 
 */
void joystick_init(void);

/**
 * @brief Read the joystick position and update menu based on the input
 * 
 */
void joystick_read(void);

/**
 * @brief Update menu based on if the button is pressed
 * 
 */
void joystick_read_button_polled(void);

/**
 * @brief Calibration for joystick values
 * 
 * @param step Step of the calibration. I.e left value or middle value
 */
void joystick_calibration_sequence(uint8_t step);

/**
 * @brief Transmit the joystick positions on the can bus
 * 
 */
void joystick_can_transmit_pos(uint8_t can_id);

/**
 * @brief Check if the button for extending solenoid is pressed
 * 
 */
void joystick_extend_solenoid(void);

#endif //JOYSTICK_H