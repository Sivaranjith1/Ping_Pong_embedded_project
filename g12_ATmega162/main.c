/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>
#include "USART/usart.h"


int main(void)
{
    const usart_option_t usart_option = {
      .baudrate = 9600  
    };
    usart_init(&usart_instance_1, usart_option);
    /* Replace with your application code */
    unsigned char data_in = 'A';
    while (1) 
    {
        data_in = usart_receive();
        usart_transmit(&usart_instance_1, data_in);
    }
}

