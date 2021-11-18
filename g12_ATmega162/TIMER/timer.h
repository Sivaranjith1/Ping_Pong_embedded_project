#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);

uint8_t timer_get_time(void);

void timer_start(void);

void timer_stop(void);

#endif