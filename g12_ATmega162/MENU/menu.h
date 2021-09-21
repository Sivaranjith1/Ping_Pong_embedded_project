#ifndef MENU_H
#define MENU_H

/*
TO-DO:
init-funksjon
redraw
FSM

meny innhold:
- start/play
- highscore
- quit
- options
	- brightness
	- calibrate joystick
	- set difficulty
	- single/multiplayer
	- main menu
- Fancy title

extra:
- Musikk (8-bit mario-esque)
*/


void menu_init(void);

void menu_current_menu_draw(void);

void menu_increment_arrow(int incrementation);

void menu_update_menu(void);

#endif //MENU_H