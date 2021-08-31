/*
 * gpio.c
 *
 * Created: 31.08.2021 11:48:31
 *  Author: Ask
 */ 
#include "gpio.h"

void gpio_pin_enable(uint8_t pin, uint8_t port){
	port |= 1 << pin;
}

void gpio_pin_disable(uint8_t pin, uint8_t port){
	uint8_t val = 0x00;
	val &= 1 << pin;
	port &= ~val;
}

uint8_t gpio_pin_read(uint8_t pin, uint8_t port){
	return port << pin;
}

void gpio_pin_toggle(uint8_t pin, uint8_t port){
	uint8_t current_value = gpio_pin_read(pin, port);
	if (current_value){
		gpio_pin_disable(pin, port);
	}
	else{
		gpio_pin_enable(pin, port);
	}
}