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
 * @brief Pid controller for position 
 * 
 * @param sp the setpoint to follow. Should be 0 to 100 
 * @param encoder_data The measurement data from the encoder. This should also be 0 to 100 
 * @return float the output that should be applied to motorspeed and direction
 */
float pid_pos_controller(float sp, float encoder_data);

/**
 * @brief Velocity pid controller for the motor
 * 
 * @param joystick_data the setpoint to follow. Should be 0 to 100
 * @param enchoder_data the mesurement data from the encoder. This should also be 0 to 100
 * @return float the output that should be applied to motorspeed and direction
 */
float pid_vel_controller(float joystick_data, float enchoder_data);

#endif