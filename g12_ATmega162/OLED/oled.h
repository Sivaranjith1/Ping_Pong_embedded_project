/*
 * IncFile1.h
 *
 * Created: 9/14/2021 8:47:57 AM
 *  Author: Steffen Folåsen
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>
#include <string.h>

/**
 * @brief Initializes the OLED screen with the recomended settings given in 
 * chapter 9.4 in the datasheet.
 * 
 */
void oled_init(void);

/**
 * @brief Turns off all LEDs by writing 0 to every position
 */
void oled_reset(void);

// Not in use atm
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

/**
 * @brief Clears an entire segment by writing 0 to all the columns
 *
 * @param line Segment to be cleared.
 */
void oled_clear_line(uint8_t line);

/**
 * @brief Uses oled_goto_line in conjunction with oled_goto_column in order to place pointers
 * to both segment and column. Please refer to their documentation for further info.
 *
 * @param line Segment we wish to use
 * @param column Column we wish to place the pointer at. 
 */
void oled_pos(uint8_t line, uint8_t column);

/**
 * @brief Puts data out on the data bus through the use of the external memory functions
 *
 * @param data Data to be put out on the bus, and subsequently writted to the OLED data registers.
 */
void oled_write_data(char data);

/**
 * @brief Writes a character to the screen. Worth noting that not all characters are supported.
 * The complete list of implemented characters can be found in fonts.h.
 * 
 * @param data Character to be written to the screen.
 */
void oled_print_char(char data);

/**
 * @brief Uses the oled_print_char function to print an array 
 *
 * @param data String (char-array) to be written to the screen
 */
void oled_print(char* data);

/**
 * @brief Sets the brightness between 0 - 255, which are the limits of the OLED screen.
 *
 * @param level How bright the screen should be adjusted to be.
 */
void oled_set_brightness(uint8_t level);

/**
 * @brief Test function that creates an arrow on the LED screen
 * 
 * @param row What page that is being used (see data sheet). There are 8 pages
 * (PAGE0 ... PAGE7), each consisting of 128 columns with 8 vertical slots associated with them.
 * @param col Which coloumn we want the arrow to start at.
 */
void oled_print_arrow(uint8_t row, uint8_t col);


/**
 * @brief Gradually changes brightness from 0 to 255 over a set interval of time, 
 * giving the screen the a fade-in like effect.
 */
void oled_fade_in(void);

void oled_fade_out(void);

void oled_turn_off(void);
#endif /* OLED_H_ */