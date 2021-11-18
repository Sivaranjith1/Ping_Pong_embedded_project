/**
 * @file goal_handler.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Driver for keeping account of Goals, it read the IR sensor value. Depends on the ADC
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GOAL_HANDLER_H
#define GOAL_HANDLER_H

#include <stdint.h>

/**
 * @brief Read the adc value and check if there are a goal or not
 * 
 * @return uint8_t 1 if the sensor is blocked and there is a goal else 0
 */
uint8_t goal_check_for_goal(void);

/**
 * @brief Get the number of goals scored
 * 
 * @return uint8_t number of goals scored
 */
uint8_t goal_get_goals(void);

#endif