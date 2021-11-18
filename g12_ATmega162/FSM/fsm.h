/**
 * @file fsm.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Finite state machine with a event queue that will change action based on the event
 * @note based on barr groups event-driven system: https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef FSM_H_
#define FSM_H_
#include <stdint.h>

/*
 * Timer events
 */
#define FSM_EV_TIMER_1          10U //when timer 1 is activated, common for all states
#define FSM_EV_STATE_TIMER_1    11U //when timer 1 is activated, specific for the current state
#define FSM_EV_TIMER_3          12U
#define FSM_EV_STATE_TIMER_3    13U

/*
 * Can events
 */
#define FSM_EV_CAN_RX_0         20U //when receiving a can message in frame 0
#define FSM_EV_CAN_RX_1         21U //when receiving a can message in frame 1

/*
 * Joystick events
 */
#define FSM_EV_JOYSTICK_UP      30U
#define FSM_EV_JOYSTICK_DOWN    31U
#define FSM_EV_JOYSTICK_BUTTON  35U

/*
 * Menu events
 */
#define FSM_EV_GO_TO_PLAY       50U
#define FSM_EV_LEAVE_PLAY       51U
#define FSM_EV_GO_TO_SRAM       52U

/*
 * Calibration events
 */
#define FSM_EV_GO_TO_CAL        60U
#define FSM_EV_LEAVE_CAL        61U

/**
 * Game events
 */
#define FSM_EV_END_GAME         70U


/**
 * @brief Get a event from the event queue and perform the action based on the current state
 * 
 */
void fsm_run();

/**
 * @brief Add event to the event queue
 * 
 * @param event_id the id of the event.
 */
void fsm_add_event(uint8_t event_id);

#endif