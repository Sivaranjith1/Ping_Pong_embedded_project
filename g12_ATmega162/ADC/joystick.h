/**
 * @file joystick.h
 * @author Steffen Folåsen
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
 * @brief Transmit the joystick positions on the can bus
 * 
 */
void joystick_can_transmit_pos(void);

void joystick_poll_buttons(void);

#endif //JOYSTICK_H