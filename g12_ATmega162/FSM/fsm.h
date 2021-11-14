/**
 * @file fsm.h
 * @author your name (you@domain.com)
 * @brief 
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

void fsm_run();
void fsm_add_event(uint8_t event_id);

#endif