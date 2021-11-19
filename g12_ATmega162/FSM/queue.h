/**
 * @file queue.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Driver for creating multiple queues with function for encoding and decoding them
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

/**
 * @brief A circular buffer struct
 * 
 * @param fifo a 256 long array to store uint8_t. Since @p head and @p tail is uint8_t they will rollover
 * @param head the value that should be read next
 * @param tail the next position to enqueue data to
 */
typedef struct {
    uint8_t fifo[256]; //will use the rollover of uint8_t to reset head and tail
    uint8_t head;
    uint8_t tail; 
} queue_t;

/**
 * @brief Add element to the queue in @param queue 
 * 
 * @param queue the queue to add data to
 * @param data_in the data to add to the queue
 */
void enqueue(queue_t* queue, uint8_t data_in);

/**
 * @brief Get the head of the queue and remove it from the queue 
 * 
 * @param queue the queue to get it from
 * @param data_out the head value
 * @return uint8_t return 1 if the queue is empty and 0 if the queue is not empty
 */
uint8_t dequeue(queue_t* queue, uint8_t* data_out);

#endif