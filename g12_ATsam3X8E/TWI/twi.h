/**
 * @file twi.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Set-up for TWI and I2C use, sadly ran out of time before being able to finalise its use,
 * but could easily be set up to communicate with other devices (currently set-up with a raspberry pi in mind).
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TWI_H_
#define TWI_H_

#include <stdint.h>

/**
 * @brief Initilises TWI0, follows the procedure of;
 * Setting PINA17 & PINA18 to peripheral
 * Enables TWI0 in PMC
 * Sets T_low = T_high = T_mck/8
 * Disables slave mode, enables master mode
 * Sets master mode to write to the slave address
 * Enables interrupt
 */
void twi_init(void);

/**
 * @brief Puts data out on the data line, one byte at a time
 * 
 * @param data byte to be put out on the data line
 */
void twi_send_byte(uint8_t data);

/**
 * @brief Interrupt handler for TWI0, currently only used for debugging
 * 
 */
void TWI0_Handler(void);

#endif