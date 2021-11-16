#include <stdint.h>
#include <float.h>
#include "../CAN/can_messages.h"

enum cal_range {MIN, MAX};
enum cal_channel {JOYSTICK_X, JOYSTICK_Y, SLIDER_R, SLIDER_L};

/**
 * @brief position of the joysticks and sliders, the values will be between -1 and 1.
 * 
 */
typedef struct
{
    float pos_x;
    float pos_y;
    float slider_l;
    float slider_r;
} joystick_t;

typedef struct
{
    float range_min;
    float range_idle;
    float range_max;
} joystick_calibrate_t;

void joystick_set_offset_calibration(enum cal_channel, char* data);

void joystick_set_range_calibration(enum cal_channel, enum cal_range, char* data);

can_joystick_pos_t joystick_convert(char* data);

void joystick_init();

void joystick_pulse_on(void);

void joystick_pulse_off(void);