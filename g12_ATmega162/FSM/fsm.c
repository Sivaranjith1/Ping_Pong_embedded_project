#include "fsm.h"
#include "queue.h"

static void fsm_state_menu(uint8_t event_id);

static queue_t fsm_queue;
static void (*current_state)(uint8_t) = &fsm_state_menu;



void fsm_run(){
    uint8_t event_id;

    uint8_t queue_state = dequeue(&fsm_queue, &event_id);
    //if(queue_state == 1) return; //do nothing if the queue is empty

    switch (event_id)
    {
    
    default: 
    {
        (*current_state)(event_id);
        break;
    }
    }
    
}

void fsm_add_event(uint8_t event_id){
    enqueue(&fsm_queue, event_id);
}

static void fsm_state_menu(uint8_t event_id){
    
}