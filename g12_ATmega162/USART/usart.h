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

#define USART_UBRR(BAUD) (F_CPU/(16*BAUD) - 1)

typedef struct {
    uint8_t baudrate;
} usart_option_t;

typedef struct {
    uint8_t udr;
    uint8_t ucsra;
    uint8_t uscrb;
    uint8_t uscrc;
    uint8_t ubrrl;
    uint8_t ubrrh;
} usart_instance_t;

const usart_instance_t usart_instance_0 = {
    .udr    = UDR0;
    .ucsra  = UCSR0A;
    .uscrb  = UCSR0B;
    .uscrc  = UCSR0C;
    .ubrrl  = UBRR0L;
    .ubrrh  = UBRR0H;   
};

void usart_init(const usart_instance_t* usart_instance, usart_option_t* usart_option);

void usart_transmit(const usart_instance_t* usart_instance, unsigned char data);


#endif /* USART_H_ */