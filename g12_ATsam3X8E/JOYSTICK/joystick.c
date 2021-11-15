#include "joystick.h"

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
		printf("Y Offset: %i\n\r", (int)(joystick_y_calibration.range_idle*100));
		break;
	}
	case JOYSTICK_X:{
		joystick_x_calibration.range_idle = data[channel];
		printf("X Offset: %i\n\r", (int)(joystick_x_calibration.range_idle*100));
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
			printf("Y MIN: %i\n\r", (int)(joystick_y_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_y_calibration.range_max = data[channel];
			printf("Y MAX: %i\n\r", (int)(joystick_y_calibration.range_max*100));
		}
		break;
	}
	case JOYSTICK_X:{
		if(range == MIN){
			joystick_x_calibration.range_min = data[channel];
			printf("X MIN: %i\n\r", (int)(joystick_x_calibration.range_min*100));
		}
		else if(range == MAX){
			joystick_x_calibration.range_max = data[channel];
			printf("X MAX: %i\n\r", (int)(joystick_x_calibration.range_max*100));
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

	if (pos_x >= joystick_x_calibration.range_idle){
		output.x_pos = 0.5*(pos_x - (float)joystick_x_calibration.range_idle)/((float)joystick_x_calibration.range_max - (float)joystick_x_calibration.range_idle) + 0.5;
	}
	else if(pos_x < joystick_x_calibration.range_idle){
		output.x_pos = 0.5*(pos_x - (float)joystick_x_calibration.range_min)/((float)joystick_x_calibration.range_idle - (float)joystick_x_calibration.range_min);
	}
	if (pos_y >= joystick_y_calibration.range_idle){
		output.y_pos = 0.5*(pos_y - (float)joystick_y_calibration.range_idle)/((float)joystick_y_calibration.range_max - (float)joystick_y_calibration.range_idle) + 0.5;
	}
	else if(pos_y < joystick_y_calibration.range_idle){
		output.y_pos = 0.5*(pos_y - (float)joystick_y_calibration.range_min)/((float)joystick_y_calibration.range_idle - (float)joystick_y_calibration.range_min);
	}
	
	//output.slider_l = (slider_l - slider_l_calibration.offset) / (slider_l_calibration.range_max - slider_l_calibration.range_min) - 1;
	//output.slider_r = (slider_r - slider_r_calibration.offset) / (slider_r_calibration.range_max - slider_r_calibration.range_min) - 1;

	return output;
}