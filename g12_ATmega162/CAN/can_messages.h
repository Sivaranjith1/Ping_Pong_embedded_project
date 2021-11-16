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

// ------------------------
//          Request
// ------------------------
#define CAN_BUTTON_PRESSED_ID 0x40

// ------------------------
//          Messages
// ------------------------
#define CAN_GOAL_SCORED_ID          0x20

// state of the atmega
#define CAN_FSM_STATE_ID             0x45
typedef enum {FSM_MENU, FSM_PLAY, FSM_CALIBRATION} can_fsm_state_t;

// joystick position data
#define CAN_JOYSTICK_POS_ID         0x50

// calibration for joystick values
#define CAN_CAL_JOYSTICK_IDLE_ID    0x60
#define CAN_CAL_JOYSTICK_UP_ID      0x61
#define CAN_CAL_JOYSTICK_DOWN_ID    0x62
#define CAN_CAL_JOYSTICK_LEFT_ID    0x63
#define CAN_CAL_JOYSTICK_RIGHT_ID   0x64


/**
 * @brief Handle incomming can messages and do the required actions
 * 
 * @param can_msg the incoming frame. A pointer to can_frame_t
 * @return uint8_t return success(0) if the id is defined. Returns failure(1) if the id is not defined
 */
uint8_t can_process_message(can_frame_t* can_msg);

#endif