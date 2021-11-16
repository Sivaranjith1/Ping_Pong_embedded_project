#include "goal_handler.h"
#include "adc.h"

#define GOAL_CHANNEL 0
#define GOAL_ALPHA 0.5 // For the EMA filter
#define VOLTAGE_NOISE 1.5 // limit for logical 0 or 1

static uint8_t goal_counter = 0;
static uint8_t goal_is_blocked = 1;
static uint8_t goal_adc_read_state(uint8_t channel);


static uint8_t goal_adc_read_state(uint8_t channel){
    if(adc_get_ema_filtered_data(channel, GOAL_ALPHA) < VOLTAGE_NOISE)
    {
        return 1;   
    }
    
    else
    {
        return 0;
    }
}

uint8_t goal_check_for_goal(void){
    uint8_t scored = 0;
    if (goal_adc_read_state(GOAL_CHANNEL))
    {
        if(!goal_is_blocked) 
        {
            goal_counter++;
            scored = 1;
        }

        goal_is_blocked = 1;
    } 
    else 
    {
        goal_is_blocked = 0;
    }
    return scored;
}

uint8_t goal_get_goals(void){
    uint8_t goals = goal_counter;
    return goals;
}

void goal_reset_goals(void){
    goal_counter = 0;
}