/**
 * @file timer.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Timer functionality both for interrupts and in-game time counting
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
 * @brief Initialises TC 1 and 3, as well as their interrupts.
 * Both have adjustable frequencies, and are enabled in compare mode.
 * TC 1 uses MCK/64, while TC uses MCK/256 
 */
void timer_init(void);

/**
 * @brief Gives the time since the clock started, used for counting in-game time.
 * 
 * @return uint16_t The time(in seconds) since timer started.
 */
uint16_t timer_get_time(void);

/**
 * @brief Tells whether the game is currently playing, and thus whether the timer
 * should be counting upwards
 * @return uint8_t Either 0 or 1 depending on if the game is playing or not.
 */
uint8_t timer_get_play();

/**
 * @brief Starts the timer, sets @p play to 1
 * 
 */
void timer_start(void);

/**
 * @brief Stops the timer, sets @p play to 0
 * 
 */
void timer_stop(void);

#endif