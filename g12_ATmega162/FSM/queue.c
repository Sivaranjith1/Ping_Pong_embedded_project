#include "queue.h"

void enqueue(queue_t* queue, uint8_t data_in){
    queue->fifo[queue->tail++] = data_in;
}

uint8_t dequeue(queue_t* queue, uint8_t* data_out){
    if(queue->head == queue->tail){
        *data_out = 0;
        return 1;
    }

    *data_out = queue->fifo[queue->head++];
    return 0;
}