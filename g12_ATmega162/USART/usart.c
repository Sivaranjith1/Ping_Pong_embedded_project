/*
 * usart.c
 *
 * Created: 31.08.2021 10:57:33
 *  Author: Sivaranjith Sivarasa
 */ 

#include "usart.h"
extern usart_instance_t usart_instance_0 = {
     .udr    = &(UDR0),
     .ucsra  = &(UCSR0A),
     .uscrb  = &(UCSR0B),
     .uscrc  = &(UCSR0C),
     .ubrrl  = &(UBRR0L),
     .ubrrh  = &(UBRR0H)
 };
 
 extern usart_instance_t usart_instance_1 = {
     .udr    = &(UDR1),
     .ucsra  = &(UCSR1A),
     .uscrb  = &(UCSR1B),
     .uscrc  = &(UCSR1C),
     .ubrrl  = &(UBRR1L),
     .ubrrh  = &(UBRR1H)
 };

void usart_init(usart_instance_t* usart_instance, usart_option_t* usart_option){
    const unsigned int ubrr = USART_UBRR(usart_option->baudrate);
    
	UBRR0H = (uint8_t)31>>8;
    UBRR0L = (uint8_t)31;
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0); //use the zeros as both will be the same
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

void usart_transmit(usart_instance_t* usart_instance, unsigned char data){
    /* Wait for empty transmit buffer */
    while ( ! (UCSR0A & (1 << UDRE0)));
    
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char usart_receive(void){
    while ( ! (UCSR0A & (1 << RXC0)));
    
    return UDR0;
}

void uart_putchar(char c, unsigned char stream)
{
	if (c == '\n'){
		uart_putchar('\r', stream);
	}
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}
