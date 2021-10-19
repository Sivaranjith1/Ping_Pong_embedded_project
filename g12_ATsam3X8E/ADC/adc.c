#include "adc.h"
#include "sam.h"

void adc_init(void){
    ADC->ADC_MR |= (1 << 1) | (1 << 0); //Prescaler = 0, Timer enabled for CH0
    ADC->ADC_CHER |= (1 << 0); // Enable channel 0
}

void adc_start_conversion(void){
    ADC->ADC_CR |= (1 << 1);
}

void adc_stop_conversion(void){
    ADC->ADC_CR &= ~(1 << 1);
}