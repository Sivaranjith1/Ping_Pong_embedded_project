#include "adc.h"
#include "sam.h"

#include "../UART/printf-stdarg.h"

#define ADC_NUM_CHANNELS 16

static float adc_last_value[ADC_NUM_CHANNELS] = { 0 };

static float adc_ema_filter(float newest_update, float last_update, float alpha);

void ADC_Handler(void){
    printf("Hello from ADCS controller \n\r");

    NVIC_ClearPendingIRQ(ADC_IRQn);
}

void adc_init(void){
    PIOA->PIO_PDR |= PIO_PDR_P2;   // Disables IO on pin 2
	PIOA->PIO_ABSR |= PIO_ABSR_P2; // Selects peripheral on pin 2

    PMC->PMC_PCR = PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); //enable ADC in PMC

    ADC->ADC_MR = ADC_MR_TRGSEL_ADC_TRIG0 | ADC_MR_TRGEN_DIS | ADC_MR_TRACKTIM(1) | ADC_MR_STARTUP_SUT8 | ADC_MR_SETTLING_AST3; //Prescaler = 0, Timer enabled for CH0, Tracking time 2 periods, 8 periods SUT, settling time 3
    //ADC->ADC_MR = ADC_MR_FREERUN_ON | ADC_MR_TRGSEL_ADC_TRIG0 | ADC_MR_TRGEN_DIS | ADC_MR_TRACKTIM(1) | ADC_MR_STARTUP_SUT8; //Prescaler = 0, Timer enabled for CH0, Tracking time 2 periods, 8 periods SUT
    ADC->ADC_CHER |= ADC_CHER_CH0; // Enable channel 0
	
    
    //Enable interrupt for conversion finished on channel 0 and data ready
    
    ADC->ADC_IER |= ADC_IER_EOC0 | ADC_IER_DRDY | ADC_IER_RXBUFF; 
    // NVIC_EnableIRQ(TC0_IRQn); // Enable interrupt for timer channel 0
    NVIC_EnableIRQ(ADC_IRQn); // Enable NVIC interrupt
    
    
    ADC->ADC_MR |= ADC_MR_TRGEN_EN;
}

void adc_start_conversion(void){
    ADC->ADC_CR |= (1 << 1);
}

void adc_stop_conversion(void){
    ADC->ADC_CR &= ~(1 << 1);
}

float adc_get_data(uint8_t channel){
    //return (float)ADC->ADC_CDR[channel]/1000;
    return ADC->ADC_LCDR/1000;
}

float adc_get_ema_filtered_data(uint8_t channel, float alpha){
    float last_update = adc_last_value[channel];
    float newest_update = adc_get_data(0);
    float filtered_value = adc_ema_filter(newest_update, last_update, alpha);

    adc_last_value[channel] = filtered_value;
    return filtered_value;
}

static float adc_ema_filter(float newest_update, float last_update, float alpha){
    return alpha*newest_update + (1 - alpha)*last_update;
}

