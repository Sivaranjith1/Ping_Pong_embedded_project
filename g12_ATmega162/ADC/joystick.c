#include "joystick.h"
#include "adc.h"
#include "../MENU/menu.h"
#include "../GPIO/gpio.h"

uint8_t move_menu = 0;
static can_frame_t joystick_data;

void joystick_read(void){
    pos_t pos_data = pos_read();
    joystick_data = (can_frame_t){
      .id = 0x01, 
      .rtr = DATA_FRAME, 
      .data_len = 8, 
      .data.f32 = {pos_data.pos_x, pos_data.pos_y}
      };

    if(pos_data.pos_y >= 0.5){
      if(!move_menu){

        menu_increment_arrow(-1);
        oled_reset();
        menu_current_menu_draw();
      }
        move_menu = 1;
    } else if(pos_data.pos_y <= -0.5){
      if(!move_menu){
        menu_increment_arrow(1);
        oled_reset();
        menu_current_menu_draw();
      }
      move_menu = 1;

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
  float test_print = *(float*)(joystick_data.data.char_array);
  printf("josfd %d \n", (uint8_t)(test_print * 100));
  can_transmit(&joystick_data);
}