#include "can_messages.h"
#include "../FSM/fsm.h"

uint8_t can_process_message(can_frame_t* can_msg){
    switch(can_msg->id){
        case CAN_GOAL_SCORED_ID:
        {
            fsm_add_event(FSM_EV_END_GAME);
            break;
        }
        default:
        {
            return 1;
        }
    }

    return 0;
}