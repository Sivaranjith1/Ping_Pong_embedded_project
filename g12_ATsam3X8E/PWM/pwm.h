/**
 * @file pwm.h
 * @author your name (you@domain.com)
 * @brief 
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
 * @brief 
 * 
 */
void pwm_init(void);

/**
 * @brief 
 * 
 * @param duty_cycle 
 * @param channel 
 */
void pwm_update_duty_cycle(float duty_cycle, uint8_t channel);

float pwm_deg_to_duty_cycle(float deg);

void pwm_update_from_joystick(float *data);

#endif
