#include "joystick.h"
#include "sam.h"
#include "../system_config.h"
#include "../EEFC/eefc.h"

#define SOLENOID_HZ 25 // Hz = 50 / SOLENOID_HZ

#if JOYSTICK_DEBUG
#include "../UART/printf-stdarg.h"
#define JOYSTICK_DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define JOYSTICK_DEBUG_PRINT(...)
#endif // JOYSTICK_DEBUG

static uint8_t solenoid_extended = 0;
static uint8_t solenoid_counter = 0;

joystick_calibrate_t joystick_x_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xFF
};

joystick_calibrate_t joystick_y_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xFF
};

joystick_calibrate_t slider_l_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xff
};

joystick_calibrate_t slider_r_calibration = {
	.range_min = 0,
	.range_idle = 0x7F,
	.range_max = 0xff
};

/**
 * @brief Loads joystick calibration data from FLASH memory
 * 
 */

static void joystick_load_calibration(void){
	uint32_t *data= eefc_read_single_page(FLASH_PAGE_JOYSTICK_CALIBRATION);
	joystick_x_calibration.range_min = (float)data[0];
	joystick_x_calibration.range_max = (float)data[1];
	joystick_y_calibration.range_min = (float)data[2];
	joystick_y_calibration.range_max = (float)data[3];
	joystick_x_calibration.range_idle = (float)data[4];
	joystick_y_calibration.range_idle = (float)data[5];
	JOYSTICK_DEBUG_PRINT("FLASH X MIN %d\n\r", (int)(joystick_x_calibration.range_min*100));
	JOYSTICK_DEBUG_PRINT("FLASH X MAX %d\n\r", (int)(joystick_x_calibration.range_max*100));
	JOYSTICK_DEBUG_PRINT("FLASH Y MIN %d\n\r", (int)(joystick_y_calibration.range_min*100));
	JOYSTICK_DEBUG_PRINT("FLASH Y MAX %d\n\r", (int)(joystick_y_calibration.range_max*100));
	JOYSTICK_DEBUG_PRINT("FLASH X MAX %d\n\r", (int)(joystick_x_calibration.range_idle*100));
	JOYSTICK_DEBUG_PRINT("FLASH X MAX %d\n\r", (int)(joystick_y_calibration.range_idle*100));
}

void joystick_store_calibration(void){
	uint32_t data[8];
	data[0] = joystick_x_calibration.range_min;
	data[1] = joystick_x_calibration.range_max;
	data[2] = joystick_y_calibration.range_min;
	data[3] = joystick_y_calibration.range_max;
	data[4] = joystick_x_calibration.range_idle;
	data[5] = joystick_y_calibration.range_idle;
	data[6]	= 0;
	data[7]	= 0;
	eefc_write_page(FLASH_PAGE_JOYSTICK_CALIBRATION, data);
}

void joystick_init(){
	//joystick_load_calibration();

	// Set-up for button pulse
	PIOC->PIO_OER |= PIO_OER_P12;
	PIOC->PIO_SODR |= PIO_SODR_P12;
}

void joystick_set_offset_calibration(enum cal_channel channel, char* data){
	switch (channel)
	{
	case SLIDER_L:
		break;
	case SLIDER_R:
		break;
	case JOYSTICK_Y:
	{
		joystick_y_calibration.range_idle = data[channel];
		JOYSTICK_DEBUG_PRINT("Y Offset: %d\n\r", (int)(joystick_y_calibration.range_idle*100));
		break;
	}
	case JOYSTICK_X:{
		joystick_x_calibration.range_idle = data[channel];
		JOYSTICK_DEBUG_PRINT("X Offset: %d\n\r", (int)(joystick_x_calibration.range_idle*100));
		break;
	}
	default:
		break;
	}
}

void joystick_set_range_calibration(enum cal_channel channel, enum cal_range range, char* data){
	switch (channel)
	{
	case SLIDER_L:
		if(range == MIN){
			slider_l_calibration.range_min = data[channel];
		}
		else if(range == MAX){
			slider_l_calibration.range_max = data[channel];
		}
		break;
	case SLIDER_R:
		if(range == MIN){
			slider_r_calibration.range_min = data[channel];
		}
		else if(range == MAX){
			slider_r_calibration.range_max = data[channel];
		}
		break;
	case JOYSTICK_Y:{
		if(range == MIN){
			joystick_y_calibration.range_min = data[channel];
			JOYSTICK_DEBUG_PRINT("Y MIN: %d\n\r", (int)(joystick_y_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_y_calibration.range_max = data[channel];
			JOYSTICK_DEBUG_PRINT("Y MAX: %d\n\r", (int)(joystick_y_calibration.range_max*100));
		}
		break;
	}
	case JOYSTICK_X:{
		if(range == MIN){
			joystick_x_calibration.range_min = data[channel];
			JOYSTICK_DEBUG_PRINT("X MIN: %d\n\r", (int)(joystick_x_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_x_calibration.range_max = data[channel];
			JOYSTICK_DEBUG_PRINT("X MAX: %d\n\r", (int)(joystick_x_calibration.range_max*100));
		}
		break;
	}
	default:
		break;
	}
}

can_joystick_pos_t joystick_convert(char* data){
    float slider_r 	= data[SLIDER_L];
	float slider_l 	= data[SLIDER_R];
	float pos_y		= data[JOYSTICK_Y];
	float pos_x 	= data[JOYSTICK_X];

	//printf("pos_y : %d\n\r", (int)(pos_y));

	can_joystick_pos_t output;

	// (read_pos - offset)/(total_range_from_offset)

	if (pos_x >= joystick_x_calibration.range_idle){
		output.x_pos = 0.5*(pos_x - (float)joystick_x_calibration.range_idle)/((float)joystick_x_calibration.range_max - (float)joystick_x_calibration.range_idle) + 0.5;
		if (output.x_pos > 100)
			output.x_pos = 100;
	}
	else if(pos_x < joystick_x_calibration.range_idle){
		output.x_pos = 0.5*(pos_x - (float)joystick_x_calibration.range_min)/((float)joystick_x_calibration.range_idle - (float)joystick_x_calibration.range_min);
		if (output.x_pos < 0)
			output.x_pos = 0;
	}
	if (pos_y >= joystick_y_calibration.range_idle){
		output.y_pos = 0.5*(pos_y - (float)joystick_y_calibration.range_idle)/((float)joystick_y_calibration.range_max - (float)joystick_y_calibration.range_idle) + 0.5;
		if (output.y_pos > 100)
			output.y_pos = 100;
	}
	else if(pos_y < joystick_y_calibration.range_idle){
		output.y_pos = 0.5*(pos_y - (float)joystick_y_calibration.range_min)/((float)joystick_y_calibration.range_idle - (float)joystick_y_calibration.range_min);
		if (output.y_pos < 0)
			output.y_pos = 0;
	}
	
	//output.slider_l = (slider_l - slider_l_calibration.offset) / (slider_l_calibration.range_max - slider_l_calibration.range_min) - 1;
	//output.slider_r = (slider_r - slider_r_calibration.offset) / (slider_r_calibration.range_max - slider_r_calibration.range_min) - 1;
	return output;
}

void joystick_pulse_on(){
	// Set low
	PIOC->PIO_CODR |= PIO_CODR_P12;
	solenoid_extended = 1;
}

void joystick_pulse_off(){
	if(solenoid_extended)
	{
		solenoid_counter++;
		if(solenoid_counter == SOLENOID_HZ)
		{
			// Set high again
			PIOC->PIO_SODR |= PIO_SODR_P12;

			// Reset for future pulses
			solenoid_counter = 0;
			solenoid_extended = 0;
		}
	}
}