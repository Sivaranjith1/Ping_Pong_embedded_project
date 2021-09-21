/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 

#include <avr/io.h>

#include "system_config.h"
#include "gpio/gpio.h"
#include "ADC/adc.h"
#include "USART/usart.h"
#include "XMEM/xmem.h"
#include "OLED/oled.h"

int main(void)
{
  uint8_t temp = 0;
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();
  oled_init();
  oled_reset();
  //oled_print_arrow(1, 7);
  //oled_print_arrow(0,0);
  while(1){
		//xmem_write(0xae, OLED_BASE_ADDRESS_COMMAND); // display off
		//xmem_write(0x00, OLED_BASE_ADDRESS_DATA);
		//for(int i = 0; i < 10000; i++){}
		//xmem_write(0xaf, OLED_BASE_ADDRESS_COMMAND); // display on
		oled_print_arrow(0, 100);
		//xmem_write(0x01, OLED_BASE_ADDRESS_DATA);
		//for(int i = 0; i < 10000; i++){}
		
  }
  return 0;
}

