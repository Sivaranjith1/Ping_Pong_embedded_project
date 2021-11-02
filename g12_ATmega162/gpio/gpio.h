/**
 * @file gpio.h
 * @author Ask Øren
 * @brief Driver for controlling GPIO pins on the ATMEGA
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
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

/**
 * @brief Sets the pin high
 * 
 * @param pin pin number
 * @param port port number
 */
void gpio_pin_enable(uint8_t pin, uint8_t port);

/**
 * @brief Sets the pin low
 * 
 * @param pin pin number
 * @param port port number
 */
void gpio_pin_disable(uint8_t pin, uint8_t port);

/**
 * @brief Toggle the gpio pin
 * 
 * @param pin pin number
 * @param port port number
 */
void gpio_pin_toggle(uint8_t pin, uint8_t port);

/**
 * @brief Reads the gpio pin
 * 
 * @param pin pin number
 * @param port port number
 * @return uint8_t the state of the pin
 */
uint8_t gpio_pin_read(uint8_t pin, uint8_t port);

#endif /* GPIO_H_ */