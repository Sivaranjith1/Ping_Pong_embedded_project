/**
 * @file motor.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa 
 * @brief Motor controller driver for position
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum {
    MOTOR_LEFT,
    MOTOR_RIGHT
} motor_direction_t;

/**
 * @brief Enable the motor for controlling position 
 * 
 */
void motor_init(void);

/**
 * @brief sets the direction and speed of the motor
 * @param speed 0 - 0.5 will result in a movement to the left and 0.5 to 1 will result in a movement to the right
 */
void motor_set_speed(float speed);

/**
 * @brief Sets the direction for the motor
 * 
 * @param direction MOTOR_RIGHT will make it move it to the right, and MOTOR_LEFT will make it move to the left
 */
void motor_set_direction(motor_direction_t direction);

uint16_t motor_read_encoder(void);

#endif