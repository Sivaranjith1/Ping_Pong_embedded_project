/**
 * @file timer.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief ATSAM's internal timer drivers
 * @version 1.0
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TIMER_H
#define TIMER_H

/**
 * @brief Initialize timer channel 0 and 1
 * 
 */
void timer_init(void);

/**
 * @brief Timer interrupt handler for timer channel 0 - used for adc conversion
 * 
 */
void TC0_Handler(void);

/**
 * @brief Timer interrupt handler for timer channel 1 - used for the PID regulator
 * 
 */
void TC1_Handler(void);

/**
 * @brief Timer interrupt handler for timer channel 2 - used for CAN transfer back to node one with score
 * 
 */
void TC2_Handler(void);

#endif