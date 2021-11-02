#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "../CAN/can.h"


void joystick_read(void);

void joystick_read_button_polled(void);

void joystick_can_transmit_pos(void);

#endif //JOYSTICK_H