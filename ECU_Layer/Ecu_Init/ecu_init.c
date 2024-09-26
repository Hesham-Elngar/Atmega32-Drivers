/*
 * ecu_init.c
 *
 * Created: 8/27/2024 10:34:55 PM
 *  Author: Hesham
 */ 

#include "ecu_init.h"
Lcd_4bit lcd1={
	.en.direction=GPIO_DIRECTION_OUTPUT,.en.logic=GPIO_LOGIC_LOW,.en.port=PORTC,.en.pin=PIN0,
	.rs.direction=GPIO_DIRECTION_OUTPUT,.rs.logic=GPIO_LOGIC_LOW,.rs.port=PORTC,.rs.pin=PIN1,
	.data[0].direction=GPIO_DIRECTION_OUTPUT,.data[0].logic=GPIO_LOGIC_LOW,.data[0].port=PORTC,.data[0].pin=PIN2,
	.data[1].direction=GPIO_DIRECTION_OUTPUT,.data[1].logic=GPIO_LOGIC_LOW,.data[1].port=PORTC,.data[1].pin=PIN3,
	.data[2].direction=GPIO_DIRECTION_OUTPUT,.data[2].logic=GPIO_LOGIC_LOW,.data[2].port=PORTC,.data[2].pin=PIN4,
	.data[3].direction=GPIO_DIRECTION_OUTPUT,.data[3].logic=GPIO_LOGIC_LOW,.data[3].port=PORTC,.data[3].pin=PIN5,
};

dc_motor_t CAR_M1={
	.dc_motor_pin[DC_MOTOR_PIN1].logic=GPIO_LOGIC_LOW,.dc_motor_pin[DC_MOTOR_PIN1].direction=GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN0,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTA,
	.dc_motor_pin[DC_MOTOR_PIN2].logic=GPIO_LOGIC_LOW,.dc_motor_pin[DC_MOTOR_PIN2].direction=GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN1,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTA
};
dc_motor_t CAR_M2={
	.dc_motor_pin[DC_MOTOR_PIN1].logic=GPIO_LOGIC_LOW,.dc_motor_pin[DC_MOTOR_PIN1].direction=GPIO_DIRECTION_OUTPUT,
	.dc_motor_pin[DC_MOTOR_PIN1].pin=PIN2,.dc_motor_pin[DC_MOTOR_PIN1].port=PORTA,
	.dc_motor_pin[DC_MOTOR_PIN2].logic=GPIO_LOGIC_LOW,.dc_motor_pin[DC_MOTOR_PIN2].direction=GPIO_DIRECTION_OUTPUT ,
	.dc_motor_pin[DC_MOTOR_PIN2].pin=PIN3,.dc_motor_pin[DC_MOTOR_PIN2].port=PORTA
};

void ECU_Init()
{
	lcd_4bit_initialize(&lcd1);
// 	keypad_initialize(&keypad1);
	dc_motor_initialize(&CAR_M1);
	dc_motor_initialize(&CAR_M2);
}