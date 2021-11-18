#include "global_data.h"

static volatile can_joystick_pos_t global_joystick_data;

void global_data_set_joystick(can_joystick_pos_t* joystick_data){
    memcpy(&global_joystick_data, joystick_data, sizeof(can_joystick_pos_t));
	//printf("Global set %d %d\n\r", (int)(joystick_data->x_pos * 100), (int)(global_joystick_data.x_pos * 100));
}

void global_data_get_joystick(can_joystick_pos_t* joystick_data){
	//printf("Global get %d %d\n\r", (int)(joystick_data->x_pos * 100), (int)(global_joystick_data.x_pos * 100));
    memcpy(joystick_data, &global_joystick_data, sizeof(can_joystick_pos_t));
    
}