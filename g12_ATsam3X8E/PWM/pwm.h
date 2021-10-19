#ifndef PWM_H
#define PWM_H

#include <stdint.h>

void pwm_init(void);

void pwm_set_duty_cycle(uint8_t duty_cycle, uint8_t channel);
#endif