#include "fsm.h"
#include "queue.h"

#include "../ADC/adc.h"
#include "../OLED/oled.h"
#include "../ADC/joystick.h"
#include "../MENU/menu.h"
#include "../CAN/can_messages.h"

static void fsm_state_menu(uint8_t event_id);
static void fsm_state_play(uint8_t event_id);

static queue_t fsm_queue;
static void (*current_state)(uint8_t) = &fsm_state_menu;



void fsm_run(){
    uint8_t event_id;

    uint8_t queue_state = dequeue(&fsm_queue, &event_id);
    if(queue_state == 1) return; //do nothing if the queue is empty

    switch (event_id)
    {
        case FSM_EV_TIMER_1:
        {
            adc_start_conversion();
            oled_refresh();
            joystick_read_button_polled();
            break;
        }

        case FSM_EV_JOYSTICK_BUTTON:
        {
            menu_update_menu();
            break;
        }
    
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

/**
 * @brief the state for when the avr in in the main menu
 * 
 * @param event_id the id of the events
 */
static void fsm_state_menu(uint8_t event_id){
    switch (event_id)
    {
        case FSM_EV_STATE_TIMER_1:
        {
            joystick_read();
            break;
        }

        case FSM_EV_JOYSTICK_UP:
        {
            menu_increment_arrow(-1);
            oled_reset();
            menu_current_menu_draw();
            break;
        }

        case FSM_EV_JOYSTICK_DOWN:
        {
            menu_increment_arrow(1);
            oled_reset();
            menu_current_menu_draw();
            break;
        }

        case FSM_EV_GO_TO_PLAY:
        {
            current_state = &fsm_state_play;
        }
        
        default:
            break;
    }
}

/**
 * @brief the state for when the avr is playing the game
 * 
 * @param event_id the id of the events
 */
static void fsm_state_play(uint8_t event_id){
    switch (event_id)
    {
        case FSM_EV_STATE_TIMER_1:
        {
            joystick_can_transmit_pos();
            break;    
        }

        case FSM_EV_LEAVE_PLAY:
        {
            current_state = &fsm_state_menu;
            break;
        }
    
        default:
            break;
    }
}