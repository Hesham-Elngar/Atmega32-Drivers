/*
 * US.h
 *
 * Created: 9/23/2024 11:17:35 AM
 *  Author: super magic
 */ 


#ifndef US_H_
#define US_H_
#include "../../MCAL_Layer/Gpio/gpio.h"
#include <util/delay.h>


#define DONE 1

extern volatile uint8_t capture_done;
extern volatile uint16_t rising_edge_time;
extern volatile uint16_t falling_edge_time;


typedef struct
{
	GPIO_Pin_Config Trigger_pin;
	GPIO_Pin_Config Echo_pin; 
}US_Sensor_t;

void HAL_US_Sensor_Init(US_Sensor_t* US_Sensor_obj);
void HAL_US_Sensor_Trigger(US_Sensor_t* US_Sensor_obj);
uint16_t HAL_US_Sensor_get_pulse_width();
uint16_t HAL_US_Sensor_Meaure_Distance(US_Sensor_t* US_Sensor_obj,uint16_t duration);

#endif /* US_H_ */