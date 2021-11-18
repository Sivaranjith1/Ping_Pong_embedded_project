#include "can_messages.h"

#include "../GLOBAL_DATA/global_data.h"
#include "../system_config.h"
#include "../JOYSTICK/joystick.h"
#include "../MOTOR/motor.h"

#if CAN_DEBUG
#include "../UART/printf-stdarg.h"
#define CAN_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define CAN_DEBUG_PRINT(...)
#endif // CAN_DEBUG

#if CAN_DEBUG_BUTTON
#include "../UART/printf-stdarg.h"
#define CAN_DEBUG_BUTTON_PRINT(...) printf(__VA_ARGS__)
#else
#define CAN_DEBUG_BUTTON_PRINT(...)
#endif // Button

uint8_t can_process_message(CAN_MESSAGE* can_msg){
    switch (can_msg->id)
    {
    case CAN_JOYSTICK_POS_ID:
    {
        can_joystick_pos_t pos_message = joystick_convert(can_msg->data.char_array);
        global_data_set_joystick(&pos_message);
        CAN_DEBUG_PRINT("Pos XY: %d %d\n\r", (int)(pos_message.x_pos*100), (int)(pos_message.y_pos*100));
        break;
    }
    case CAN_BUTTON_PRESSED_ID:
    {
        CAN_DEBUG_BUTTON_PRINT("Button pressed: %d\n\r", can_msg->data.char_array[0]);
        joystick_pulse_on();
        break;
    }
    case (CAN_CAL_JOYSTICK_IDLE_ID):
    {
        joystick_set_offset_calibration(JOYSTICK_X, can_msg->data.char_array);
        joystick_set_offset_calibration(JOYSTICK_Y, can_msg->data.char_array);
        break;
    }
    case (CAN_CAL_JOYSTICK_UP_ID):
    {
        joystick_set_range_calibration(JOYSTICK_Y, MAX, can_msg->data.char_array);
        break;
    }
    case (CAN_CAL_JOYSTICK_DOWN_ID):
    {
        joystick_set_range_calibration(JOYSTICK_Y, MIN, can_msg->data.char_array);
        break;
    }
    case (CAN_CAL_JOYSTICK_LEFT_ID):
    {
        joystick_set_range_calibration(JOYSTICK_X, MIN, can_msg->data.char_array);
        break;
    }
    case (CAN_CAL_JOYSTICK_RIGHT_ID):
    {
        joystick_set_range_calibration(JOYSTICK_X, MAX, can_msg->data.char_array);
        break;
    }
    case (CAN_FSM_STATE_ID):
    {
        if(can_msg->data.char_array[0] == FSM_PLAY){
            motor_enable_soft();
        } else {
            motor_disable_soft();
        }
        break;
    }
    default:
        return 1;
    }

    return 0;
}
