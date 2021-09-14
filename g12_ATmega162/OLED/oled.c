﻿/*
 * CFile1.c
 *
 * Created: 9/14/2021 8:47:37 AM
 *  Author: Steffen Folåsen
 */ 

#include "oled.h"
#include "../system_config.h"
#include "../XMEM/xmem.h"


//Command ON
void oled_init(void){
	xmem_write(0xae, OLED_BASE_ADDRESS_COMMAND); // display off
	xmem_write(0x00, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xa1, OLED_BASE_ADDRESS_COMMAND); //segment remap
	xmem_write(0x00, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xda, OLED_BASE_ADDRESS_COMMAND); //common pads hardware: alternative
	xmem_write(0x12, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xc8, OLED_BASE_ADDRESS_COMMAND); //common output scan direction:com63~com0
	xmem_write(0xa8, OLED_BASE_ADDRESS_COMMAND); //multiple, x ration mode:63
	xmem_write(0x3f, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xd5, OLED_BASE_ADDRESS_COMMAND); //display divide ratio/osc. freq. mode
	xmem_write(0x80, OLED_BASE_ADDRESS_DATA);
	xmem_write(0x81, OLED_BASE_ADDRESS_COMMAND); //contrast control
	xmem_write(0x50, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xd9, OLED_BASE_ADDRESS_COMMAND); //set pre-charge period
	xmem_write(0x21, OLED_BASE_ADDRESS_DATA);
	xmem_write(0x20, OLED_BASE_ADDRESS_COMMAND); //Set Memory Addressing Mode
	xmem_write(0x02, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xdb, OLED_BASE_ADDRESS_COMMAND); //VCOM deselect level mode
	xmem_write(0x30, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xad, OLED_BASE_ADDRESS_COMMAND); //master configuration
	xmem_write(0x00, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xa4, OLED_BASE_ADDRESS_COMMAND); //out follows RAM content
	xmem_write(0x00, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xa6, OLED_BASE_ADDRESS_COMMAND); //set normal display
	xmem_write(0x01, OLED_BASE_ADDRESS_DATA);
	xmem_write(0xaf, OLED_BASE_ADDRESS_COMMAND); // display on	
	xmem_write(0x01, OLED_BASE_ADDRESS_DATA);
}

//Command ON
void oled_reset(void){
	
}

//Command ON
void oled_goto_line(uint8_t line){
	xmem_write(0xB0 | (0xF & line), OLED_BASE_ADDRESS);
}

//Command ON
void oled_goto_column(uint8_t column){
	xmem_write(0x10, OLED_BASE_ADDRESS);
	xmem_write(0xF & column, OLED_BASE_ADDRESS);
}

//Command ON
void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	oled_goto_column(column);
}

//Command OFF
void oled_write_data(char* data){
	xmem_write(data, OLED_BASE_ADDRESS_DATA);
}

//Command OFF
void oled_print_arrow(uint8_t row, uint8_t col){
	oled_pos(row, col);
	oled_write_data(0b00011000);
	oled_write_data(0b00011100);
	oled_write_data(0b00111110);
	oled_write_data(0b00011100);
	oled_write_data(0b00011000);	
}