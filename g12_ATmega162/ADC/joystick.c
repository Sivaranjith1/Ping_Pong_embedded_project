#include "joystick.h"
#include "adc.h"
#include "../MENU/menu.h"
#include "../GPIO/gpio.h"
#include "../CAN/can_messages.h"
#include "../FSM/fsm.h"

uint8_t move_menu = 0;
static uint8_t polled = 0;

void joystick_init(){
  DDRB &= ~(1 << PIN1);
  DDRB &= ~(1 << PIN2);
  PORTB |= 0x03;
}

void joystick_read(void){
  uint8_t joystick_y = adc_get_channel_data(JOYSTICK_Y)-35;

  if(joystick_y >= 90){
    if(!move_menu){
      fsm_add_event(FSM_EV_JOYSTICK_UP);
      move_menu = 1;
    }
  } else if(joystick_y <= 40){
    if(!move_menu){
      fsm_add_event(FSM_EV_JOYSTICK_DOWN);
      move_menu = 1;

    }
  } else {
    move_menu = 0;
  }
}

void joystick_calibration_sequence(uint8_t step){
  switch (step)
  {
    case 0:
    {
      oled_pos(0, 0);
      oled_print("JOYSTICK CAL");
    }
    case 1:
    {
      oled_clear_line(3);
      oled_pos(3, 0);
      oled_print("JOYSTICK LEFT");
      joystick_can_transmit_pos(CAN_CAL_JOYSTICK_LEFT_ID);
      break;
    }
    case 2:
    {
      oled_clear_line(3);
      oled_pos(3, 0);
      oled_print("JOYSTICK RIGHT");
      joystick_can_transmit_pos(CAN_CAL_JOYSTICK_RIGHT_ID);
      break;
    }
    case 3:
    {
      oled_clear_line(3);
      oled_pos(3, 0);
      oled_print("JOYSTICK DOWN");
      joystick_can_transmit_pos(CAN_CAL_JOYSTICK_DOWN_ID);
      break;
    }
    case 4:
    {
      oled_clear_line(3);
      oled_pos(3, 0);
      oled_print("JOYSTICK UP");
      joystick_can_transmit_pos(CAN_CAL_JOYSTICK_UP_ID);
      break;
    }
    case 5:
    {
      oled_clear_line(3);
      oled_pos(3, 0);
      oled_print("JOYSTICK IDLE");
      joystick_can_transmit_pos(CAN_CAL_JOYSTICK_IDLE_ID);
      break;   
    }
    case 6:
    {
      oled_clear_line(0);
      oled_clear_line(3);
      oled_pos(0, 0);
      oled_print("CALIBRATION");
      oled_pos(1, 0);
      oled_print("FINNISHED");
      break;
    }

    default:
      break;
    }
}

void joystick_read_button_polled(void){
    if(!gpio_pin_read(PB3, PINB)){
      while(!gpio_pin_read(PB3, PINB));
      fsm_add_event(FSM_EV_JOYSTICK_BUTTON);
    }
}

void joystick_can_transmit_pos(uint8_t can_id){

  can_frame_t joystick_data = {
    .id = can_id, 
    .rtr = DATA_FRAME, 
    .data_len = 4, 
    .data.char_array = {
      adc_get_channel_data(0),
      adc_get_channel_data(1),
      adc_get_channel_data(2),
      adc_get_channel_data(3)
    }
  };
  can_transmit(&joystick_data);
}

void joystick_poll_buttons(){
  if((gpio_pin_read(PINB0, PINB) | gpio_pin_read(PINB1, PINB)) && !polled){
    can_frame_t button_pressed = {
      .id = CAN_BUTTON_PRESSED_ID,
      .rtr = DATA_FRAME,
      .data_len = 1,
      .data.char_array = { 1 }
    };
    can_transmit(&button_pressed);
    polled = 1;
  }
  else if(!(gpio_pin_read(PINB0, PINB) | gpio_pin_read(PINB1, PINB))){
    polled = 0;
  }
}