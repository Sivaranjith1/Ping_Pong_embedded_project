#include "pid.h"
#include <stdint.h>

static float k_p = 0.2;
static float k_i = 0;
static float k_d = 0;

static float pid_integral = 0;
static float pid_derivative = 0;

static float T = 0.02;

void pid_init(void){
    
}

float pid_controller(float joystick_data, float encoder_data){
    float e = joystick_data - encoder_data;
    printf("JS: %d\n\r", (uint8_t)joystick_data*100);
    printf("ED: %d\n\r", (uint8_t)encoder_data*100);
    printf("Error: %d\n\r", (uint8_t)e*100);
    pid_integral += e;
    float u = k_p*e + T*k_i*pid_integral + (k_d/T)*(e - pid_derivative);
    pid_derivative = e;
    return u;
}