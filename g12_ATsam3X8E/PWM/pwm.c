#include "pwm.h"
#include "sam.h"

static uint32_t pwm_duty_cycle_math(uint8_t duty_cycle, uint8_t channel);

void pwm_init(void){
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //Enable PWM in PMC, subtraction 32 since PMC_PCER0 is 32 bit long
    PWM->PWM_CLK |= PWM_CLK_PREA(0x01) | PWM_CLK_DIVA(0x01) | PWM_CLK_PREB(0x01) | PWM_CLK_DIVB(0x01);

	PWM->PWM_ENA |= PWM_ENA_CHID6 | PWM_ENA_CHID5;   //Enables PWM on channel 5 & 6

    PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_2;
    PWM->PWM_CH_NUM[6].PWM_CMR = PWM_CMR_CPRE_MCK_DIV_2;
    
    PWM->PWM_CH_NUM[5].PWM_CPRD = PWM_CPRD_CPRD(4200000000);
    PWM->PWM_CH_NUM[6].PWM_CPRD = PWM_CPRD_CPRD(4200000000);
    
    PIOC->PIO_PDR |= PIO_PDR_P18;   //Disables IO on pin 45
	PIOC->PIO_ABSR |= PIO_ABSR_P18; // Selects peripheral on pin 45
    PIOC->PIO_PDR |= PIO_PDR_P19;   //Disables IO on pin 44
    PIOC->PIO_ABSR |= PIO_ABSR_P19; //  Selects peripheral on pin 44
	
} 
// Htijnar is back
void pwm_set_duty_cycle(uint8_t duty_cycle, uint8_t channel){
    //uint32_t cdty_value = (PWM->PWM_CH_NUM[channel].PWM_CPRD*(100 - duty_cycle)/100) + 0.0009;
    uint32_t cdty_value = pwm_duty_cycle_math(duty_cycle, channel);
    printf("Val2: %d\n\r", cdty_value);
	PWM->PWM_CH_NUM[channel].PWM_CDTY = PWM_CDTY_CDTY(cdty_value);
}

static uint32_t pwm_duty_cycle_math(uint8_t duty_cycle, uint8_t channel){
    uint32_t nominator = PWM->PWM_CH_NUM[channel].PWM_CPRD * ((100 - (float)duty_cycle)/100);
    printf("Val1: %d\n\r", nominator);
    return nominator * PWM->PWM_CH_NUM[channel].PWM_CMR;
}