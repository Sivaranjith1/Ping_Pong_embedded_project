/**
 * @file menu.h
 * @author Ask Øren, Steffen Folåsen, Sivaranjith Sivarasa
 * @brief Driver for controlling the menu and elements on the screen
 * @version 0.1
 * @date 2021-10-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MENU_H
#define MENU_H

#include <stdint.h>

/**
 * @brief Draws the elements in the main menu. Calls the
 * @p oled_fade_in function.
 * 
 */
void menu_init(void);

/**
 * @brief Draws the current menu that the @p current_menu pointer (local pointer)
 * is pointing at. This is chosen by the arrow controlled by the joystick.
 *  
 */
void menu_current_menu_draw(void);

/**
 * @brief Increments the arrow one line (page in the OLED data sheet) 
 * depending on the @p incrementation value
 * 
 * @param incrementation Incerementation value, can be eighter 1, -1, or 0
 */
void menu_increment_arrow(int incrementation);

/**
 * @brief Resets the sram and the OLED before it updates the @p current_menu
 * pointer and draws the new menu.
 * 
 */
void menu_update_menu(void);

/**
 * @brief Updates the game timer indicating how long you have been playing for
 * 
 * @param time the time to be written to the screen
 */
void menu_update_timer(uint8_t time);

/**
 * @brief Stops the game, displays game over on the screen
 * 
 */
void menu_draw_game_over();

#endif //MENU_H