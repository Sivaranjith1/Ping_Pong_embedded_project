#include "can_messages.h"

#include "../GLOBAL_DATA/global_data.h"
#include "../system_config.h"

#if CAN_DEBUG
#include "../UART/printf-stdarg.h"
#define CAN_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define CAN_DEBUG_PRINT(...)
#endif // CAN_DEBUG

uint8_t can_process_message(CAN_MESSAGE* can_msg){
    switch (can_msg->id)
    {
    case CAN_JOYSTICK_POS_ID:
    {
        can_joystick_pos_t pos_message = *(can_joystick_pos_t*)(can_msg->data.char_array);
        global_data_set_joystick(&pos_message);
        CAN_DEBUG_PRINT("Pos XY: %d %d\n\r", (int)(pos_message.x_pos*100), (int)(pos_message.y_pos*100));
        break;
    }
    case CAN_BUTTON_PRESSED_ID:
    {
        CAN_DEBUG_PRINT("Button pressed: %d\n\r", can_msg->data.char_array[0]);
    }
    default:
        return 1;
    }

    return 0;
}
