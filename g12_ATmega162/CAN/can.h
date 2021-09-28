#ifndef CAN_H
#define CAN_H

#include <stdint.h>

typedef enum {
    DATA_FRAME = 0,
    REMOTE_TRANSMIT_REQUEST = 1
} can_rtr_t;


typedef struct {
    uint16_t id;
    can_rtr_t rtr;
    uint8_t data_len;
    uint8_t data[8];
} can_frame_t;


void can_init(void);

void can_transmit(can_frame_t* can_frame);

#endif