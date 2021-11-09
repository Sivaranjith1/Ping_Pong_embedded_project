#include "joystick.h"
#include "adc.h"
#include "../MENU/menu.h"
#include "../GPIO/gpio.h"
#include "../CAN/can_messages.h"

uint8_t move_menu = 0;
static uint8_t polled = 0;

void joystick_init(){
  DDRB &= ~(1 << PIN1);
  DDRB &= ~(1 << PIN2);
  PORTB |= 0x03;
}

void joystick_read(void){
    pos_t pos_data = pos_read();

    if(pos_data.pos_y >= 0.7){
      if(!move_menu){

        menu_increment_arrow(-1);
        oled_reset();
        menu_current_menu_draw();
        move_menu = 1;
      }
    } else if(pos_data.pos_y <= 0.3){
      if(!move_menu){
        menu_increment_arrow(1);
        oled_reset();
        menu_current_menu_draw();
        move_menu = 1;

      }
    } else {
      move_menu = 0;
    }
}

void joystick_read_button_polled(void){
    if(!gpio_pin_read(PB3, PINB)){
      oled_reset();
      menu_update_menu();
    }
}

void joystick_can_transmit_pos(){
  pos_t pos_data = pos_read();
  can_frame_t joystick_data = {
    .id = CAN_JOYSTICK_POS_ID, 
    .rtr = DATA_FRAME, 
    .data_len = 8, 
    .data.f32 = {pos_data.pos_x, pos_data.pos_y}
  };
  can_transmit(&joystick_data);
}

void joystick_calibrate(){

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