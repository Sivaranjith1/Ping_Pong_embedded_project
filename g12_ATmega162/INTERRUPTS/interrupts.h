/**
 * @file interrupts.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Enables pin-interrupts for the ATmega162
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include <avr/interrupt.h>

/**
 * @brief Initialises interrupts on pins INT0 and INT2
 * 
 */
void interrupt_init(void);

#endif