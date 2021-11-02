/**
 * @file pid.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa 
 * @brief Driver for creating pid controllers.
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef PID_H
#define PID_H

#include <stdint.h>

/**
 * @brief Initialize the pid controller with the 
 * 
 */
void pid_init(void);

/**
 * @brief 
 * 
 * @param data 
 * @return uint16_t 
 */
float pid_controller(float sp, float encoder_data);

#endif