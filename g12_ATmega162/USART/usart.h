/*
 * usart.h
 *
 * Created: 31.08.2021 10:57:19
 *  Author: Sivaranjith Sivarasa
 */ 
#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "../system_config.h"

#define USART_UBRR(BAUD) ((F_CPU/10)/(1.6*BAUD) - 1)

typedef struct {
    volatile uint8_t* udr;
    volatile uint8_t* ucsra;
    volatile uint8_t* uscrb;
    volatile uint8_t* uscrc;
    volatile uint8_t* ubrrl;
    volatile uint8_t* ubrrh;
} usart_instance_t;


extern usart_instance_t usart_instance_0;
extern usart_instance_t usart_instance_1;

void usart_init(usart_instance_t* usart_instance, uint16_t baudrate);

void usart_transmit(usart_instance_t* usart_instance, unsigned char data);

unsigned char usart_receive(void);

int usart_putchar(char c, FILE* stream);


#endif /* USART_H_ */
