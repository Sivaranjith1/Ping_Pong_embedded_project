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
    CAN_DEBUG_PRINT("Message with id: %d\n\r", can_msg->id);
    switch (can_msg->id)
    {
    case CAN_JOYSTICK_POS_ID:
    {
        can_joystick_pos_t pos_message = *(can_joystick_pos_t*)(can_msg->data.char_array);
        global_data_set_joystick(&pos_message);
        break;
    }
    default:
        return 1;
    }

    return 0;
}
