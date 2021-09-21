/*
 * IncFile1.h
 *
 * Created: 9/14/2021 8:47:57 AM
 *  Author: Steffen Folåsen
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>

/**
 * @brief Initializes the OLED screen with the recomended settings given in 
 * chapet 9.4 in the datasheet.
 * 
 */
void oled_init(void);

void oled_reset(void);

void oled_home(void);


/**
 * @brief Places a pointer to a given PAGE on the OLED board.
 * 
 * @param line What page that is being used (see data sheet). There are 8 pages
 * (PAGE0 ... PAGE7) and each page is one byte
 */
void oled_goto_line(uint8_t line);

/**
 * @brief Places a pointer to a given column on the OLED board.
 * 
 * @param column Desired column to be written.
 */
void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t line, uint8_t column);

void oled_write_data(char data);

void oled_print(char* data);

void oled_print_char(char data);

void oled_set_brightness(uint8_t level);

/**
 * @brief Test function that creates an arrow on the LED screen
 * 
 * @param row What page that is being used (see data sheet). There are 8 pages
 * (PAGE0 ... PAGE7) and each page is one byte
 * @param col 
 */
void oled_print_arrow(uint8_t row, uint8_t col);

#endif /* OLED_H_ */