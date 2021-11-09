#ifndef GLOBAL_DATA_H_
#define GLOBAL_DATA_H_

#include "../CAN/can_messages.h"

void global_data_set_joystick(can_joystick_pos_t* joystick_data);
void global_data_get_joystick(can_joystick_pos_t* joystick_data);

#endif