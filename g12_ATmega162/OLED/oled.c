/*
 * CFile1.c
 *
 * Created: 9/14/2021 8:47:37 AM
 *  Author: Steffen Folåsen
 */ 

#include "oled.h"
#include "../system_config.h"
#include "../XMEM/xmem.h"
#include "fonts.h"

#include <string.h>

#define FADE_LENGTH 10000


void oled_init(void){
	xmem_write(0xAE, OLED_BASE_ADDRESS_COMMAND); // display off
	xmem_write(0xA1, OLED_BASE_ADDRESS_COMMAND); //segment remap
	xmem_write(0xDA, OLED_BASE_ADDRESS_COMMAND); //common pads hardware: alternative
	xmem_write(0x12, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xC8, OLED_BASE_ADDRESS_COMMAND); //common output scan direction:com63~com0
	xmem_write(0xA8, OLED_BASE_ADDRESS_COMMAND); //multiple, x ration mode:63
	xmem_write(0x3F, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xD5, OLED_BASE_ADDRESS_COMMAND); //display divide ratio/osc. freq. mode
	xmem_write(0x80, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0x81, OLED_BASE_ADDRESS_COMMAND); //contrast control
	xmem_write(0x50, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xD9, OLED_BASE_ADDRESS_COMMAND); //set pre-charge period
	xmem_write(0x21, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0x20, OLED_BASE_ADDRESS_COMMAND); //Set Memory Addressing Mode
	xmem_write(0x02, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xDB, OLED_BASE_ADDRESS_COMMAND); //VCOM deselect level mode
	xmem_write(0x30, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xAD, OLED_BASE_ADDRESS_COMMAND); //master configuration
	xmem_write(0x00, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(0xA4, OLED_BASE_ADDRESS_COMMAND); //out follows RAM content
	xmem_write(0xA6, OLED_BASE_ADDRESS_COMMAND); //set normal display
	xmem_write(0xAF, OLED_BASE_ADDRESS_COMMAND); // display on	
	oled_reset();
}

void oled_reset(void){
	for (uint8_t i = 0; i < 8; i++){
		oled_clear_line(i);
	}
}

void oled_goto_line(uint8_t line){
	if(line > 7){
		return;
	}

	xmem_write(0xB0 | line, OLED_BASE_ADDRESS_COMMAND); // Set page
}

void oled_goto_column(uint8_t column){
	if(column > 127){
		return;
	}

	xmem_write(0x00 | (0x0F & column), OLED_BASE_ADDRESS_COMMAND); // set the low address
	xmem_write(0x10  | (0xF0 & column) >> 4, OLED_BASE_ADDRESS_COMMAND); // set the high address
}

void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_write_data(char data){
	xmem_write(data, OLED_BASE_ADDRESS_DATA);
}

void oled_print_arrow(uint8_t row, uint8_t col){
	oled_pos(row, col);
	oled_write_data(0b00011000);
	oled_write_data(0b00011000);
	oled_write_data(0b00111110);
	oled_write_data(0b00011100);
	oled_write_data(0b00011000);	
}

void oled_set_brightness(uint8_t level){
	xmem_write(0x81, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(level, OLED_BASE_ADDRESS_COMMAND);
}

void oled_clear_line(uint8_t line){
	oled_pos(line, 0);
	for(uint8_t i = 0; i < 128; i++){
		oled_write_data(0x00);
	}
	oled_goto_line(line);
}

void oled_print_char(char data){
	for(uint8_t i = 0; i < FONT8_SIZE; i++){
		oled_write_data(pgm_read_byte(&font8[data - ASCII_OFFSET][i]));
	}
}

void oled_print(char* data){
	for(uint8_t i = 0; i < strlen(data); i++){
		oled_print_char(data[i]);
	}
}

void oled_fade_in(void){
	for(uint8_t i = 0; i < 255; i++){
		oled_set_brightness(i);
		for(uint16_t i = 0; i < FADE_LENGTH; i++);
    }
}

void oled_fade_out(void){
	for (uint8_t i = 255; i > 0; i--)
	{
		oled_set_brightness(i);
		for(uint16_t i = 0; i < FADE_LENGTH; i++);
	}	
}

void oled_turn_off(void){
	oled_fade_out();
	xmem_write(0xAE, OLED_BASE_ADDRESS_COMMAND);
}

/* void oled_save_data_to_sram(uint8_t data, uint8_t line, uint8_t col){
 	xmem_write(OLED_SRAM_ADDRESS_START + 128*line + col, data);
}

uint8_t oled_read_previous_data(uint8_t line, uint8_t col){
	return xmem_read(OLED_SRAM_ADDRESS_START + 128*line + col);
}

void oled_print(char* data){
	for(uint8_t i = 0; i < strlen(data); i++){
		oled_redraw(data[i]);
	}
}

void oled_redraw(uint8_t data, uint8_t line, uint8_t col){
	uint8_t old_state = oled_read_previous_data(line, col);
	if(old_state != data){
		oled_save_data_to_sram(data, line, col);
		oled_write_data(data);
	}
	else{
		return;
	}
}
*/
