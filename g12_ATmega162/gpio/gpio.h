/*
 * gpio.h
 *
 * Created: 31.08.2021 11:42:16
 * Author: Ask
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include <avr/io.h>

/*Ta i mot port, pin, og set direction (input/output)
Enable
Disable
Toggle kanskje
Read
*/


void gpio_pin_enable(uint8_t pin, uint8_t port);
void gpio_pin_disable(uint8_t pin, uint8_t port);
void gpio_pin_toggle(uint8_t pin, uint8_t port);

uint8_t gpio_pin_read(uint8_t pin, uint8_t port);

#endif /* GPIO_H_ */