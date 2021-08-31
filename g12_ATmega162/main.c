/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>

#include "system_config.h"
#include "USART/usart.h"

int main(void)
{
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  FILE* output = fdevopen(usart_putchar, 0);
  
  uint16_t address = 0x2000;
  unsigned char *p = (unsigned char *) (address + 1);
  
  DDRC = 0xFF;
  PORTC = 0x00;
  
  SFIOR = (1 << XMM1) | (1 << XMM0);
  
  *p = 0xaa;
  
  SFIOR = 0x00;
  *p = 0x55;
}

