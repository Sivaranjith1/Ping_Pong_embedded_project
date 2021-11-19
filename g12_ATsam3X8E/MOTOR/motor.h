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
 * @brief Will enable the dacc output for the motor in software
 * 
 */
void motor_enable_soft(void);

/**
 * @brief Will disable the dacc output for the motor in software
 * 
 */
void motor_disable_soft(void);

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

/**
 * @brief Read the raw encoder values. Negative values will indicate moving to the left
 * 
 * @return int16_t A 2ers complement value of the encoder position
 */
int16_t motor_read_encoder(void);

/**
 * @brief Resets the encoder. This will say that the current position will give a read-out of zero
 * 
 */
void motor_reset_encoder();

/**
 * @brief get the position of the motor on the shaft relative to the walls. 0 is the position next to the leftwall
 * 
 * @return float 0 to 1 scaled value of the motor position on the shaft 
 */
float motor_get_position();

/**
 * @brief set the current position to the max value. Used for calibration of the motor. This will be position 1 for @p motor_get_position()
 * 
 */
void motor_position_set_max_value();

#endif