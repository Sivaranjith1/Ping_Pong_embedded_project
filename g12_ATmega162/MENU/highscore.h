/**
 * @file highscore.h
 * @author Ask Øren, Sivaranjith Sivarasa, Steffen Folåsen
 * @brief Driver from a sorted highscore table in sram
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

#include <stdint.h>

#define HIGHSCORE_SCORES_NUM      5U

/**
 * @brief Create a array with size @p HIGHSCORE_SCORES_NUM initialized to zero in sram
 * 
 */
void highscore_init();

/**
 * @brief Add a score to the highscore table. If it is lower than existing scores, it will be ignored
 * 
 * @param new_score the new highscore
 */
void highscore_add_score(uint8_t new_score);

/**
 * @brief Gets the highscore for the choosen place
 * 
 * @param place The place to get the score from. Should not be bigger than @p HIGHSCORE_SCORES_NUM
 * @return uint8_t the score
 */
uint8_t highscore_get_scores(uint8_t place);

#endif