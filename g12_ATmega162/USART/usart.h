/**
 * @file usart.h
 * @author Sivaranjith Sivarasa
 * @brief USART driver for ATMEGA162
 * @version 0.1
 * @date 2021-08-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "../system_config.h"

#define USART_UBRR(BAUD) ((F_CPU/10)/(1.6*BAUD) - 1)
#define PRINT_F_USART &usart_instance_0

/**
 * @brief A usart instance and its corresponding registors. This is used to choose with instance to read/send from 
 * 
 */
typedef struct {
    volatile uint8_t* udr;
    volatile uint8_t* ucsra;
    volatile uint8_t* uscrb;
    volatile uint8_t* uscrc;
    volatile uint8_t* ubrrl;
    volatile uint8_t* ubrrh;
} usart_instance_t;

//Usart instances corresponding to the instances in the AVR datasheet
extern usart_instance_t usart_instance_0;
extern usart_instance_t usart_instance_1;

/**
 * @brief initializing usart instance for async clock and given
 * 
 * @param usart_instance One of the ATMEGA162 usart instances with its registors
 * @param baudrate baudrate to use on the usart instance
 */
void usart_init(usart_instance_t* usart_instance, uint16_t baudrate);

/**
 * @brief Transmit a character on the usart instance
 * 
 * @param usart_instance Usart instance to use for transmission
 * @param data The character to transmit
 */
void usart_transmit(usart_instance_t* usart_instance, unsigned char data);

unsigned char usart_receive(void);

/**
 * @brief Transmission for printf function
 * 
 * @param c the character to transmit
 * @return int 0 if transmission was a success
 */
int usart_putchar(char c, FILE* stream);


#endif /* USART_H_ */
