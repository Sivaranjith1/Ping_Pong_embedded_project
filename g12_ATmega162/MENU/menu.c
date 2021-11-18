#define MENU_NAME_LEN 15
#define OPTIONS_CHILDREN 4

#include "menu.h"
#include "highscore.h"
#include "../ADC/adc.h"
#include "../ADC/joystick.h"
#include "../OLED/oled.h"
#include "../SRAM/sram.h"
#include "../FSM/fsm.h"
#include <stdint.h>
#include "../system_config.h"

 

/////////////////////////////////////////////////////////////////////////
//  Local Function Pointer Declaration
/////////////////////////////////////////////////////////////////////////

typedef void (*menu_draw_function)(void);
/**
 * 
 */
typedef struct menu_item menu_item;
struct menu_item {
    char name[MENU_NAME_LEN];
    menu_item* parent;
    uint8_t num_children;
    menu_item* children[OPTIONS_CHILDREN];
    menu_draw_function draw_func;
};

/////////////////////////////////////////////////////////////////////////
//  Local Menu Items Definitions
/////////////////////////////////////////////////////////////////////////

static menu_item main_menu;
static menu_item play;
static menu_item options;
static menu_item high_score;
static menu_item quit;
static menu_item calibrate_joystick;
static menu_item brightness;
static menu_item sram_test;

/////////////////////////////////////////////////////////////////////////
//  Local Functions Definitions
/////////////////////////////////////////////////////////////////////////

static void menu_children_dropdown_draw(menu_item* menu);

static void menu_main_draw(void);
static void menu_play_draw(void);
static void menu_options_draw(void);
static void menu_high_score_draw(void);
static void menu_quit_draw(void);
static void menu_calibrate_draw(void);
static void menu_brightness_draw(void);
static void menu_sram_test(void);

/////////////////////////////////////////////////////////////////////////
//  Local Menu Items Declarations
/////////////////////////////////////////////////////////////////////////

static menu_item* current_menu = &main_menu;
static uint8_t menu_children_arrow_line = 0;

static menu_item main_menu = {
    .name = "MAIN MENU",
    .num_children = 4,
    .parent = 0,
    .children = {&play, &options, &high_score, &quit},
    .draw_func = &menu_main_draw
};

static menu_item play = {
    .name = "PLAY",
    .num_children = 0,
    .parent = &main_menu,
    .children = {0},
    .draw_func = &menu_play_draw
};

static menu_item high_score = {
    .name = "HIGH SCORE",
    .num_children = 0,
    .parent = &main_menu,
    .children = {0},
    .draw_func = &menu_high_score_draw
};

static menu_item options = {
    .name = "OPTIONS",
    .num_children = 3,
    .parent = &main_menu,
    .children = {&brightness, &calibrate_joystick, &sram_test},
    .draw_func = &menu_options_draw
};

static menu_item quit = {
    .name = "QUIT",
    .num_children = 0,
    .parent = &main_menu,
    .children = {0},
    .draw_func = &menu_quit_draw
};

static menu_item calibrate_joystick = {
    .name = "CALIBRATE",
    .num_children = 0,
    .parent = &options,
    .children = {0},
    .draw_func = &menu_calibrate_draw
};

static menu_item brightness = {
    .name = "BRIGHTNESS",
    .num_children = 0,
    .parent = &options,
    .children = {0},
    .draw_func = &menu_brightness_draw
};

static menu_item sram_test = {
    .name = "SRAM TEST",
    .num_children = 0,
    .parent = &options,
    .children = {0},
    .draw_func = &menu_sram_test
};


/////////////////////////////////////////////////////////////////////////
//  Local Function Declarations
/////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 * @param menu 
 */
static void menu_children_dropdown_draw(menu_item* menu){
    oled_print_arrow(menu_children_arrow_line, 0);
    for (uint8_t i = 0; i < menu->num_children; i++)
    {
        oled_pos(i, 20);
        oled_print(menu->children[i]->name);
    }
    
    if(menu->parent != 0){
        oled_pos(menu->num_children, 20);
        oled_print(menu->parent->name);
    }
    
}

// Menu draw functions
static void menu_main_draw(void){
    menu_children_dropdown_draw(&main_menu);
}

static void menu_play_draw(void){
    menu_children_dropdown_draw(&play);
    oled_pos(6, 10);
    oled_print("It's a trap");
    
}

static void menu_options_draw(void){
    menu_children_dropdown_draw(&options);
}

static void menu_quit_draw(void){
    oled_turn_off();
}

static void menu_high_score_draw(void){
    menu_children_dropdown_draw(&high_score);

    for(uint8_t i = 0; i < HIGHSCORE_SCORES_NUM; i++){
        oled_pos(1 + i, 30);
        unsigned char score_char[8] = {0};
        sprintf(score_char, "P%d: %d", i, highscore_get_scores(i));
        oled_print(score_char);
    }
}

static void menu_calibrate_draw(void){
}

static void menu_brightness_draw(void){
    uint8_t brightness = oled_get_brightness();
    unsigned char bright_char[5] = {0};
    sprintf(bright_char, "%d", brightness);
    oled_clear_line(2);

    oled_pos(0,0);
    oled_print("CURRENT");
    oled_pos(1,0);
    oled_print("BRIGHTNESS");
    oled_pos(2,40);
    oled_print(bright_char);
    // NOT DONE, NEEDS SUPPORT FOR JOYSTICK MOVEMENT
}

static void menu_sram_test(void){
    menu_children_dropdown_draw(&sram_test);
    oled_pos(3, 30);
    oled_print("Running test");
}

/////////////////////////////////////////////////////////////////////////
//  Global Function Declarations
/////////////////////////////////////////////////////////////////////////

void menu_init(){
    menu_main_draw();
    oled_fade_in();
}

void menu_current_menu_draw(void){
    (*current_menu->draw_func)();
}

void menu_increment_arrow(int incrementation){
    menu_children_arrow_line += incrementation;

    if(menu_children_arrow_line < 0) {
        menu_children_arrow_line = current_menu->num_children - 1;
    } else if(menu_children_arrow_line >= current_menu->num_children && current_menu->parent == 0){
        menu_children_arrow_line = 0;
    } else if(menu_children_arrow_line > current_menu->num_children && current_menu->parent != 0){
        menu_children_arrow_line = 0;
    }
}

void menu_update_menu(void){
    menu_item* prev_menu = current_menu;
    if(menu_children_arrow_line < current_menu->num_children){   
        current_menu = current_menu->children[menu_children_arrow_line];
    } else if(current_menu->parent != 0){
        current_menu = current_menu->parent;
    }


    if(current_menu == &play){
        fsm_add_event(FSM_EV_GO_TO_PLAY);
    }
    else if(prev_menu == &play && current_menu != &play){
        oled_clear_line(3);
        fsm_add_event(FSM_EV_LEAVE_PLAY);
    }
    else if(current_menu == &calibrate_joystick){
        fsm_add_event(FSM_EV_GO_TO_CAL);
    }
    else if(prev_menu == &calibrate_joystick && current_menu != &calibrate_joystick){
        fsm_add_event(FSM_EV_LEAVE_CAL);
    }
    else if(current_menu == &brightness){
        fsm_add_event(FSM_EV_GO_TO_BRIGHTNESS);
    }
    else if(prev_menu == &brightness && current_menu != &brightness){
        fsm_add_event(FSM_EV_LEAVE_BRIGHTNESS);
    }
    else if(current_menu == &sram_test){
        fsm_add_event(FSM_EV_GO_TO_SRAM);
    }

    oled_reset();
    menu_children_arrow_line = 0;
    menu_current_menu_draw();
}

void menu_update_timer(uint16_t time){
    unsigned char time_char[8] = {0};
    sprintf(time_char, "%d", time);
    oled_clear_line(3);
	oled_pos(3,20);
	oled_print("TIME:");
    oled_pos(3, 60);
	oled_print(time_char);
}

void menu_draw_game_over(){
    oled_clear_line(6);
    oled_pos(6, 10);
    oled_print("Game over");
}