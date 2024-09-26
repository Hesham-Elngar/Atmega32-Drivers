/*
 * motor.h
 *
 * Created: 9/25/2024 1:49:44 AM
 *  Author: super magic
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

/* ----------------- Includes -----------------*/
#include"../../MCAL_Layer/Gpio/gpio.h"
/* ----------------- Macro Declarations -----------------*/
#define DC_MOTOR_ON_STATUS  1
#define DC_MOTOR_OFF_STATUS 0

#define DC_MOTOR_PIN1 0
#define DC_MOTOR_PIN2 1

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
	GPIO_Pin_Config dc_motor_pin[2];
}dc_motor_t;

/* ----------------- Software Interfaces Declarations -----------------*/
void dc_motor_initialize(const dc_motor_t *_dc_motor);
void dc_motor_move_right(const dc_motor_t *_dc_motor);
void dc_motor_move_left(const dc_motor_t *_dc_motor);
void dc_motor_stop(const dc_motor_t *_dc_motor);


#endif /* MOTOR_H_ */