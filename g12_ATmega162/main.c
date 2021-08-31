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
	while(1){
		unsigned char data_in = 'A';
		unsigned char output = fdevopen(usart_receive());
		printf(output);
	}
}

