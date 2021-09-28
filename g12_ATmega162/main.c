/*
 * g12_ATmega162.c
 *
 * Created: 31.08.2021 08:28:05
 * Author : Sivaranjith Sivarasa
 */ 



#include "system_config.h"
#include "ADC/adc.h"
#include "ADC/joystick.h"
#include "USART/usart.h"
#include "XMEM/xmem.h"
#include "OLED/oled.h"
#include "MENU/menu.h"
#include "GPIO/gpio.h"
#include "SRAM/sram.h"
#include "SPI/spi.h"
#include "CAN/can.h"
#include "CAN/mcp2515.h"


void init(void){
  usart_init(&usart_instance_0, MAX233_BAUDRATE);
  xmem_init();
  sram_init();
  oled_init();
  menu_init();
  spi_init();
  can_init();
}

int main(void)
{
  init();
  printf("Hello world eller noe sånt\n");
  can_frame_t test_frame = {
    .id = 69,
    .rtr = 0,
    .data_len = 1,
    .data = {69}
  };

  can_transmit(&test_frame);

  while(1){
    //joystick_read();
    //joystick_read_button_polled();

    printf("%d \n", mcp_read(0x0E));
  }
  return 0;
}

