#include "adc.h"
#include "sam.h"


#include "../UART/printf-stdarg.h"
#include "../system_config.h"

#define ADC_NUM_CHANNELS 16

#if ADC_DEBUG
#define ADC_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define ADC_DEBUG_PRINT(...)
#endif // ADC_DEBUG


static float adc_latest_data[ADC_NUM_CHANNELS] = { 0 }; //the last data from the interrupt
static float adc_last_ema_value[ADC_NUM_CHANNELS] = { 0 };

static float adc_ema_filter(float newest_update, float last_update, float alpha);
static uint8_t adc_get_channel(void);
static float adc_get_lcdr_data(void);

void adc_init(void){
    //PIOA->PIO_PDR |= PIO_PDR_P16;
    //PIOA->PIO_ABSR |= PIO_ABSR_P16;
    PIOA->PIO_PDR |= PIO_PDR_P2;   // Disables IO on pin 2
	PIOA->PIO_ABSR |= PIO_ABSR_P2; // Selects peripheral on pin 2

    PMC->PMC_PCR |= PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV_MCK | (ID_ADC << PMC_PCR_PID_Pos);
    PMC->PMC_PCER1 |= 1 << (ID_ADC - 32); //enable ADC in PMC

    ADC->ADC_WPMR = (0x414443 << 8); // Disables WP

    ADC->ADC_CHER |= ADC_CHER_CH0; // Enable channel 0

    //Prescaler = 0, Hardware triggers disabled, Tracking time 2 periods, 8 periods SUT, settling time 3
    ADC->ADC_MR |= ADC_MR_TRGEN_DIS | ADC_MR_TRACKTIM(1) | ADC_MR_STARTUP_SUT8 | ADC_MR_SETTLING_AST3; 
    
    //Enable interrupt for data ready
    ADC->ADC_IER |= ADC_IER_DRDY;
    NVIC_EnableIRQ(ADC_IRQn); // Enable NVIC interrupt
    
}

void ADC_Handler(void){
    ADC_DEBUG_PRINT("ADC says EOC \n\r");
    adc_latest_data[adc_get_channel()] = adc_get_lcdr_data();
    NVIC_ClearPendingIRQ(ADC_IRQn);
}

void adc_start_conversion(void){
    ADC->ADC_CR |= (1 << 1);
}

void adc_stop_conversion(void){
    ADC->ADC_CR &= ~(1 << 1);
}

float adc_get_data(uint8_t channel){
    return adc_latest_data[channel];
}


float adc_get_ema_filtered_data(uint8_t channel, float alpha){
    float last_update = adc_last_ema_value[channel];
    float newest_update = adc_get_data(channel);
    float filtered_value = adc_ema_filter(newest_update, last_update, alpha);

    adc_last_ema_value[channel] = filtered_value;
    return filtered_value;
}

static float adc_get_lcdr_data(void){
    return (ADC->ADC_LCDR & 0xFFF)/1000;
}

static uint8_t adc_get_channel(void){
    return (ADC->ADC_LCDR >> 12);
}

static float adc_ema_filter(float newest_update, float last_update, float alpha){
    return alpha*newest_update + (1 - alpha)*last_update;
}


