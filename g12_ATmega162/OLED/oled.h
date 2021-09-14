﻿/*
 * IncFile1.h
 *
 * Created: 9/14/2021 8:47:57 AM
 *  Author: Steffen Folåsen
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <stdint.h>

void oled_init(void);

void oled_reset(void);

void oled_home(void);

void oled_goto_line(uint8_t line);

void oled_goto_column(uint8_t column);

void oled_clear_line(uint8_t line);

void oled_pos(uint8_t line, uint8_t column);

void oled_write_data(char* data);

void oled_print(char* data);

void oled_set_brightness(uint8_t level);

void oled_print_arrow(uint8_t row, uint8_t col);

#endif /* OLED_H_ */