/**
 * @file fsm.c
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Finite state machine with a event queue that will change action based on the event
 * @note based on barr groups event-driven system: https://barrgroup.com/embedded-systems/how-to/state-machines-event-driven-systems
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "fsm.h"
#include "queue.h"

#include "../ADC/adc.h"
#include "../OLED/oled.h"
#include "../ADC/joystick.h"
#include "../MENU/menu.h"
#include "../MENU/highscore.h"
#include "../CAN/can_messages.h"
#include "../XMEM/xmem.h"
#include "../TIMER/timer.h"

static void fsm_state_menu(uint8_t event_id);
static void fsm_state_calibration(uint8_t event_id);
static void fsm_state_play(uint8_t event_id);
static void fsm_state_brightness(uint8_t event_id);

static void fsm_can_transmit_state(can_fsm_state_t state);

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
            joystick_read_button_polled();
            break;
        }

        case FSM_EV_TIMER_3:
        {
            adc_start_conversion();
            oled_refresh();
            break;
        }

        case FSM_EV_CAN_RX_0:
        {
            can_frame_t can_msg;
            can_receive(0, &can_msg);
            can_process_message(&can_msg);
            break;
        }

        case FSM_EV_CAN_RX_1:
        {
            can_frame_t can_msg;
            can_receive(1, &can_msg);
            can_process_message(&can_msg);
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
            fsm_can_transmit_state(FSM_PLAY);
            timer_start();
            break;
        }
        
        case FSM_EV_GO_TO_CAL:
        {
            joystick_calibration_step = 0;
            current_state = &fsm_state_calibration;
            fsm_can_transmit_state(FSM_CALIBRATION);
            joystick_calibration_sequence(joystick_calibration_step);
            break;
        }

        case FSM_EV_GO_TO_BRIGHTNESS:
        {
            current_state = &fsm_state_brightness;
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

/**
 * @brief the state for when the avr is in calibration mode 
 * 
 * @param event_id the id of the events
 */
static void fsm_state_calibration(uint8_t event_id){
    switch (event_id)
    {
        case FSM_EV_LEAVE_CAL:
        {
            current_state = &fsm_state_menu;
            menu_update_menu();
            fsm_can_transmit_state(FSM_MENU);
            break;
        }
        case FSM_EV_JOYSTICK_BUTTON:
        {
          joystick_calibration_step += 1;
          if (joystick_calibration_step > 6) {
            fsm_add_event(FSM_EV_LEAVE_CAL);
          }
          else {
            joystick_calibration_sequence(joystick_calibration_step);
          }
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
            joystick_extend_solenoid();
            break;    
        }

        case FSM_EV_STATE_TIMER_3:
        {
            joystick_can_transmit_pos(CAN_JOYSTICK_POS_ID);
            menu_update_timer(timer_get_time());
            break;
        }

        case FSM_EV_LEAVE_PLAY:
        {
            current_state = &fsm_state_menu;
        } //Fallthrough
        case FSM_EV_END_GAME:
        {
            uint8_t is_playing = timer_get_play();
            fsm_can_transmit_state(FSM_MENU);
            timer_stop();
            menu_draw_game_over();
            if(is_playing){
                highscore_add_score(timer_get_time());
            }

            break;
        }

        case FSM_EV_JOYSTICK_BUTTON:
        {
            menu_update_menu();
            break;
        }

    
        default:
            break;
    }
}

/**
 * @brief the state for when changing the brightness, in the brightness menu
 * 
 * @param event_id the id of the events
 */
static void fsm_state_brightness(uint8_t event_id){
    uint8_t brightness = oled_get_brightness();
    switch (event_id)
    {
        case FSM_EV_STATE_TIMER_1:
        {
            joystick_read();
            break;
        }

        case FSM_EV_JOYSTICK_UP:
        {
            oled_set_brightness(brightness + 10);
            menu_current_menu_draw();
            break;
        }

        case FSM_EV_JOYSTICK_DOWN:
        {
                        
            oled_set_brightness(brightness - 10);
            menu_current_menu_draw();
            break;
        }

        case FSM_EV_JOYSTICK_BUTTON:
        {
            menu_update_menu();
            break;
        }

        case FSM_EV_LEAVE_BRIGHTNESS:
        {
            current_state = &fsm_state_menu;
            break;
        }

        default:
            break;
    }
}

static void fsm_can_transmit_state(can_fsm_state_t state){
    can_frame_t fsm_state_msg =  {
        .id = CAN_FSM_STATE_ID,
        .rtr = DATA_FRAME,
        .data_len = 1,
        .data.char_array = { state }
    };
    can_transmit(&fsm_state_msg);
}