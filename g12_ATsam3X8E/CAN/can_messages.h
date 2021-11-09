/**
 * @file can_messages.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief The ids and content of the can frames
 * @version 0.1
 * @date 2021-11-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include <stdint.h>

#include "can_controller.h"

// ------------------------
//          Request
// ------------------------

// ------------------------
//          Messages
// ------------------------

#define CAN_JOYSTICK_POS_ID 0x50
typedef struct {
    float x_pos;
    float y_pos;
} can_joystick_pos_t;

/**
 * @brief Handle incomming can messages and do the required actions
 * 
 * @param can_msg the incoming frame. A pointer to CAN_MESSAGE
 * @return uint8_t return success(0) if the id is defined. Returns failure(1) if the id is not defined
 */
uint8_t can_process_message(CAN_MESSAGE* can_msg);

#endif