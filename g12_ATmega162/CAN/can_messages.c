#include "can_messages.h"
#include "../MENU/menu.h"

uint8_t can_process_message(can_frame_t* can_msg){
    switch(can_msg.id){
        case CAN_GOAL_SCORED_ID:
        {
            menu_update_goal(can_msg[0]);
            return 0;
        }
        default:
        {
            return 1;
        }
    }
}