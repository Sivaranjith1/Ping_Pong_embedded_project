#include "pwm.h"
#include "sam.h"

static uint32_t pwm_duty_cycle_math(float duty_cycle, uint8_t channel);

void pwm_init(void){
    // Disables WP
    PIOA->PIO_WPMR = (0x50494F << 8);
    PIOB->PIO_WPMR = (0x50494F << 8);
    PIOC->PIO_WPMR = (0x50494F << 8);

    PIOC->PIO_PDR |= PIO_PDR_P18;   //Disables IO on pin 44
	PIOC->PIO_ABSR |= PIO_ABSR_P18; // Selects peripheral on pin 44
    PIOC->PIO_PDR |= PIO_PDR_P19;   //Disables IO on pin 45
    PIOC->PIO_ABSR |= PIO_ABSR_P19; //  Selects peripheral on pin 45
	
    PWM->PWM_WPCR = (0x50574D << 8); // Disables WP
    PWM->PWM_CLK |= PWM_CLK_PREA(0x05) | PWM_CLK_DIVA(0x01) | PWM_CLK_PREB(0x02) | PWM_CLK_DIVB(0x25); // Setting clk prescalers

    PWM->PWM_CH_NUM[5].PWM_CMR = PWM_CMR_CPRE_CLKB; // Using clk B for channel 5
    PWM->PWM_CH_NUM[6].PWM_CMR = PWM_CMR_CPRE_CLKB; // Using clk B for channel 6

    PMC->PMC_WPMR = (0x504D43 << 8); // Disables WP
    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_PWM << PMC_PCR_PID_Pos); // Enable PWM in PMC
	PMC->PMC_PCER1 |= 1 << (ID_PWM - 32); //Enable PWM in PMC, subtraction 32 since PMC_PCER0 is 32 bit long

    PWM->PWM_CH_NUM[5].PWM_CPRD |= PWM_CPRD_CPRD(8400000); // Setting the period to the CPRD
    PWM->PWM_CH_NUM[6].PWM_CPRD |= PWM_CPRD_CPRD(8400000); // Setting the period to the CPRD

    PWM->PWM_CH_NUM[5].PWM_CDTY |= PWM_CDTY_CDTY(pwm_duty_cycle_math(50, 5)); //Sets default value to duty cycle
	PWM->PWM_CH_NUM[6].PWM_CDTY |= PWM_CDTY_CDTY(pwm_duty_cycle_math(50, 6)); //Sets default value to duty cycle

	PWM->PWM_ENA |= PWM_ENA_CHID6 | PWM_ENA_CHID5;   //Enables PWM on channel 5 & 6
} 

void pwm_update_duty_cycle(float duty_cycle, uint8_t channel){
    uint32_t cdty_value = pwm_duty_cycle_math(duty_cycle, channel);
	PWM->PWM_CH_NUM[channel].PWM_CDTYUPD = PWM_CDTY_CDTY(cdty_value);
}

float pwm_deg_to_duty_cycle(float deg){
    // duty cycle between 4,5 - 10,5%
    if(deg > 100){
        deg -= 100;
    }
    else if(deg < 0){
        deg += 100;
    }
    float duty_cycle = 4.5 + (10.5 - 4.5) * deg / (100);
    return duty_cycle;
}

static uint32_t pwm_duty_cycle_math(float duty_cycle, uint8_t channel){
    uint32_t nominator = PWM->PWM_CH_NUM[channel].PWM_CPRD * ((100.0 - duty_cycle)/100.0); //calculate the value for CDTY or CDTYUPD register
    return nominator;
}

void pwm_update_from_joystick(float data){
    pwm_update_duty_cycle(pwm_deg_to_duty_cycle(data*100), 5);
    pwm_update_duty_cycle(pwm_deg_to_duty_cycle(data*100), 6);
}