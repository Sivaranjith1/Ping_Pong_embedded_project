/**
 * @file timer.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * @brief 
 * 
 */
void timer_init(void);

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t timer_get_time(void);

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t timer_get_play();

/**
 * @brief 
 * 
 */
void timer_start(void);

/**
 * @brief 
 * 
 */
void timer_stop(void);

#endif