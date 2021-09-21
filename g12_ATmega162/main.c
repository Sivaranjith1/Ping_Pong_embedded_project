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
#include "MENU/menu.h"

void init(void){
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();
  oled_init();
  menu_init();
}

int main(void)
{
  init();
  while(1){
    //menu_current_menu_draw();
  }
  return 0;
}

