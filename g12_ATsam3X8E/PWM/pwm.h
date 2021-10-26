/**
 * @file pwm.h
 * @author Ask Øren
 * @brief Driver for PWM on channel 5 and 6 of the ATSAM3X8E
 * @version 0.1
 * @date 2021-10-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef PWM_H
#define PWM_H

#include <stdint.h>

/**
 * @brief Initialize the channel 5 and 6 of the ATSAM with a period of 20ms
 * 
 */
void pwm_init(void);

/**
 * @brief Set the new duty cycle for the chosen channel
 * 
 * @param duty_cycle A floating value with percentage of the duty cycle. Min is 0 and max is 100
 * @param channel Channel to update the duty cycle on. Can be 5 or 6
 */
void pwm_update_duty_cycle(float duty_cycle, uint8_t channel);

/**
 * @brief Convert from percentage values to duty cycles for the servo motor
 * 
 * @param deg Percentage from 0 to 100 of the angle of the servo motor
 * @return float the duty cycle to pass to @c pwm_update_duty_cycle
 */
float pwm_deg_to_duty_cycle(float deg);

/**
 * @brief Update the pwms for the servo motor based on the joystick can message
 * 
 * @param data a array of len two
 */
void pwm_update_from_joystick(float *data);

#endif
