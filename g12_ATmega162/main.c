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
    usart_init(&usart_instance_0, &usart_option);
    /* Replace with your application code */
    int inter = 0;
    while (1) 
    {
        if((++inter) == 1000){
            inter = 0;
            usart_transmit(&usart_instance_0, 'A');
        }
    }
}

