#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

typedef struct {
    uint8_t fifo[256]; //will use the rollover of uint8_t to reset head and tail
    uint8_t head;
    uint8_t tail; 
} queue_t;

void enqueue(queue_t* queue, uint8_t data_in);

/**
 * @brief 
 * 
 * @param queue 
 * @param data_out 
 * @return uint8_t return 1 if the queue is empty and 0 if the queue is not empty
 */
uint8_t dequeue(queue_t* queue, uint8_t* data_out);

#endif