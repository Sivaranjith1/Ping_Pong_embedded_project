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
#define COLUMN_MAX_VALUE 127
#define PAGE_MAX_VALUE 7

/////////////////////////////////////////////////////////////////////////
//  Local Variables and Function Definitions
/////////////////////////////////////////////////////////////////////////
static uint8_t current_page = 0;
static uint8_t current_column = 0;

/**
 * @brief Calls upon @p xmem_write to put data out on the external memory bus
 *
 * @param data Data to be put on on the bus, and subsequently written to the OLED
 */
static void oled_write_data(unsigned char data);

/**
 * @brief Loads what the screen currently looks like, to be used for comparison in @p oled_redraw
 */
static unsigned char oled_read_previous_data(void);
static void oled_save_data_to_sram(unsigned char data);

/**
 * @brief Checks whether we have reached the end of the screen, if yes it resets the pointer to column 0
 */
static void oled_check_max_column(void);

/**
 * @brief Places a pointer to a given column on the OLED board.
 * 
 * @param column Desired column to be written.
 */
static void oled_goto_column(uint8_t column);

/**
 * @brief Places a pointer to a given PAGE on the OLED board.
 * 
 * @param line What page that is being used (see data sheet). There are 8 pages
 * (PAGE0 ... PAGE7) and each page is one byte
 */
static void oled_goto_line(uint8_t line);

/**
 * @brief Writes a character to the screen. Worth noting that not all characters are supported.
 * The complete list of implemented characters can be found in fonts.h.
 * 
 * @param data Character to be written to the screen.
 */
static void oled_print_char(unsigned char data);

/////////////////////////////////////////////////////////////////////////
//  Local Function Declarations
/////////////////////////////////////////////////////////////////////////
static void oled_write_data(unsigned char data){
	xmem_write(data, OLED_BASE_ADDRESS_DATA);
}

static unsigned char oled_read_previous_data(void){
	return (unsigned char)xmem_read(OLED_SRAM_ADDRESS_START + 128*current_page + current_column);
}

static void oled_save_data_to_sram(unsigned char data){
 	xmem_write_with_check(data, OLED_SRAM_ADDRESS_START + 128*current_page + current_column);
	oled_check_max_column();
}

static void oled_check_max_column(void){
	if(current_column == COLUMN_MAX_VALUE){
		current_column = 0;
	}
	else{
		current_column++;
	}
}

static void oled_goto_line(uint8_t line){
	if(line > 7){
		return;
	}

	xmem_write(0xB0 | line, OLED_BASE_ADDRESS_COMMAND); // Set page
	current_page = line;
}

static void oled_goto_column(uint8_t column){
	if(column > COLUMN_MAX_VALUE){
		return;
	}

	xmem_write(0x00 | (0x0F & column), OLED_BASE_ADDRESS_COMMAND); // set the low address
	xmem_write(0x10  | (0xF0 & column) >> 4, OLED_BASE_ADDRESS_COMMAND); // set the high address
	current_column = column;
}

static void oled_print_char(unsigned char data){
	for(uint8_t i = 0; i < FONT8_SIZE; i++){
		oled_redraw(pgm_read_byte(&font8[data - ASCII_OFFSET][i]));
	}
}

/////////////////////////////////////////////////////////////////////////
//  Global Function Declarations
/////////////////////////////////////////////////////////////////////////
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

void oled_pos(uint8_t line, uint8_t column){
	oled_goto_line(line);
	oled_goto_column(column);
}

void oled_print_arrow(uint8_t row, uint8_t col){
	oled_pos(row, col);
	oled_redraw(0b00011000);
	oled_redraw(0b00011000);
	oled_redraw(0b00111110);
	oled_redraw(0b00011100);
	oled_redraw(0b00011000);	
}

void oled_set_brightness(uint8_t level){
	xmem_write(0x81, OLED_BASE_ADDRESS_COMMAND);
	xmem_write(level, OLED_BASE_ADDRESS_COMMAND);
}

void oled_clear_line(uint8_t line){
	oled_pos(line, 0);
	for(uint8_t i = 0; i < 128; i++){
		oled_redraw(0x00);
	}
	oled_goto_line(line);
}

void oled_print(unsigned char* data){
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

void oled_redraw(unsigned char data){
	unsigned char old_state = oled_read_previous_data();
	oled_save_data_to_sram(data);
}

void oled_refresh(){
	for (uint8_t page = 0; page <= PAGE_MAX_VALUE; page++)
	{
		oled_pos(page, 0);
		for (uint8_t column = 0; column <= COLUMN_MAX_VALUE; column++)
		{
			unsigned char data_from_sram = (unsigned char)xmem_read(OLED_SRAM_ADDRESS_START + 128*page + column);
			oled_write_data(data_from_sram);
		}
	}
	
	oled_pos(0,0);
}