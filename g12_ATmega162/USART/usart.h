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

#include "../system_config.h"
#include "avr/io.h"

#define USART_UBRR(BAUD) ((F_CPU/10)/(1.6*BAUD) - 1)

typedef struct {
    uint16_t baudrate;
} usart_option_t;

typedef struct {
    uint8_t* udr;
    uint8_t* ucsra;
    uint8_t* uscrb;
    uint8_t* uscrc;
    uint8_t* ubrrl;
    uint8_t* ubrrh;
} usart_instance_t;


extern usart_instance_t usart_instance_0;
extern usart_instance_t usart_instance_1;

void usart_init(usart_instance_t* usart_instance, usart_option_t usart_option);

void usart_transmit(usart_instance_t* usart_instance, unsigned char data);

unsigned char usart_receive(void);

void usart_putchar(char c, unsigned char stream);


#endif /* USART_H_ */