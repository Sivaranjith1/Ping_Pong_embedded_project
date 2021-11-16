#include "pid.h"
#include <stdint.h>

#if PID_DEBUG
#include "../UART/printf-stdarg.h"
#define PID_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define PID_DEBUG_PRINT(...)
#endif // PID_DEBUG

static float k_p = 0.5;
static float k_i = 0.002;
static float k_d = 0;

static float pid_integral = 0;
static float pid_derivative = 0;

static float encoder_prev_data = 0;

static float T = 0.02;

float pid_pos_controller(float joystick_data, float encoder_data){
    float e = joystick_data - encoder_data;
    pid_integral += e;
    float u = k_p*e + T*k_i*pid_integral + (k_d/T)*(e - pid_derivative);
    pid_derivative = e;
    return u;
}

float pid_vel_controller(float joystick_data, float encoder_data){
    float encoder_speed = (encoder_data - encoder_prev_data)/T;

    if(encoder_speed > 10 || encoder_speed < -10)
    {
        encoder_speed = 0;
    }

    encoder_prev_data = encoder_data;
    
    PID_DEBUG_PRINT("JS: %d\n\r", (uint8_t)joystick_data*100);
    PID_DEBUG_PRINT("ED: %d\n\r", (uint8_t)encoder_speed*100);
    PID_DEBUG_PRINT("Error: %d\n\r", (uint8_t)e*100);

    volatile float speed = pid_pos_controller(joystick_data, encoder_speed + 0.5);
	return speed;
}