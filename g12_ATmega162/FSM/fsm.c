#include "fsm.h"
#include "queue.h"

#include "../ADC/adc.h"
#include "../OLED/oled.h"
#include "../ADC/joystick.h"
#include "../MENU/menu.h"
#include "../CAN/can_messages.h"
#include "../XMEM/xmem.h"
#include "../TIMER/timer.h"

static void fsm_state_menu(uint8_t event_id);
static void fsm_state_calibration(uint8_t event_id);
static void fsm_state_play(uint8_t event_id);

static queue_t fsm_queue;
static void (*current_state)(uint8_t) = &fsm_state_menu;

static uint8_t joystick_calibration_step;


void fsm_run(){
    uint8_t event_id;

    uint8_t queue_state = dequeue(&fsm_queue, &event_id);
    if(queue_state == 1) return; //do nothing if the queue is empty

    switch (event_id)
    {
        case FSM_EV_TIMER_1:
        {
            adc_start_conversion();
            joystick_read_button_polled();
            break;
        }

        case FSM_EV_TIMER_3:
        {
            oled_refresh();
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

        case FSM_EV_JOYSTICK_BUTTON:
        {
            menu_update_menu();
            break;
        }

        case FSM_EV_GO_TO_PLAY:
        {
            current_state = &fsm_state_play;
            timer_start();
            break;
        }
        
        case FSM_EV_GO_TO_CAL:
        {
            joystick_calibration_step = 0;
            current_state = &fsm_state_calibration;
            joystick_calibration_sequence(joystick_calibration_step);
            break;
        }

        case FSM_EV_GO_TO_SRAM:
        {
            xmem_SRAM_test();
            break;
        }

        default:
            break;
    }
}

static void fsm_state_calibration(uint8_t event_id){
    switch (event_id)
    {
        case FSM_EV_LEAVE_CAL:
        {
            current_state = &fsm_state_menu;
            break;
        }
        case FSM_EV_JOYSTICK_BUTTON:
        {
          joystick_calibration_step += 1;
          if (joystick_calibration_step > 6)
            fsm_state_calibration(FSM_EV_LEAVE_CAL);
          else
            joystick_calibration_sequence(joystick_calibration_step);
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
            joystick_can_transmit_pos(CAN_JOYSTICK_POS_ID);
            joystick_extend_solenoid();
            break;    
        }

        case FSM_EV_STATE_TIMER_3:
        {
            menu_update_timer(timer_get_time());
            break;
        }

        case FSM_EV_LEAVE_PLAY:
        {
            current_state = &fsm_state_menu;
            break;
        }

        case FSM_EV_JOYSTICK_BUTTON:
        {
            menu_update_menu();
            break;
        }

        case FSM_EV_END_GAME:
        {
            timer_stop();
            break;
        }
    
        default:
            break;
    }
}