#define MENU_NAME_LEN 15
#define OPTIONS_CHILDREN 4

#include "menu.h"
#include "../OLED/oled.h"
#include <stdint.h>

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
static menu_item set_difficulty;
static menu_item sp_mp;

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
static void menu_players_draw(void);
static void menu_difficulty_draw(void);

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
    .num_children = 4,
    .parent = &main_menu,
    .children = {&brightness, &calibrate_joystick, &set_difficulty, &sp_mp},
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

static menu_item sp_mp = {
    .name = "PLAYERS",
    .num_children = 0,
    .parent = &options,
    .children = {0},
    .draw_func = &menu_players_draw
};

static menu_item set_difficulty = {
    .name = "DIFFICULTY",
    .num_children = 0,
    .parent = &options,
    .children = {0},
    .draw_func = &menu_difficulty_draw
};

/////////////////////////////////////////////////////////////////////////
//  Local Function Declarations
/////////////////////////////////////////////////////////////////////////

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
    oled_pos(0, 50);
    oled_print("Its");
    oled_pos(1, 50);
    oled_print("A");
    oled_pos(2, 50);
    oled_print("TRAP!");
}

static void menu_options_draw(void){
    menu_children_dropdown_draw(&options);
}

static void menu_quit_draw(void){
    oled_turn_off();
}

static void menu_high_score_draw(void){}
static void menu_calibrate_draw(void){}
static void menu_brightness_draw(void){}
static void menu_players_draw(void){
    oled_pos(0, 50);
    oled_print("YOU");
    oled_pos(1, 50);
    oled_print("WANNA");
    oled_pos(2, 50);
    oled_print("PLAY");
    oled_pos(3, 50);
    oled_print("A");
    oled_pos(4, 50);
    oled_print("GAME?");
}
static void menu_difficulty_draw(void){}

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
    uint8_t t2 = current_menu->num_children;

    if(menu_children_arrow_line < 0) {
        menu_children_arrow_line = current_menu->num_children - 1;
    } else if(menu_children_arrow_line >= current_menu->num_children && current_menu->parent == 0){
        uint8_t t = current_menu->num_children;
        menu_children_arrow_line = 0;
    } else if(menu_children_arrow_line > current_menu->num_children && current_menu->parent != 0){
        uint8_t t = current_menu->num_children;
        menu_children_arrow_line = 0;
    }
}

void menu_update_menu(void){
    if(menu_children_arrow_line < current_menu->num_children){   
        current_menu = current_menu->children[menu_children_arrow_line];
    } else if(current_menu->parent != 0){
        current_menu = current_menu->parent;
    }

    menu_children_arrow_line = 0;
    menu_current_menu_draw();
	oled_fade_in();
}
