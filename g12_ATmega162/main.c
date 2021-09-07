/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>

#include "system_config.h"
#include "USART/usart.h"
#include "XMEM/xmem.h"

int main(void)
{
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();

  while(1){
	xmem_SRAM_test();
  }

  return 0;
}

