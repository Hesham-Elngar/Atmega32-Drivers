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

Keypad_t keypad1={
	.keypad_row[0].direction=GPIO_DIRECTION_OUTPUT,.keypad_row[0].logic=GPIO_LOGIC_LOW,
	.keypad_row[0].port=PORTD,.keypad_row[0].pin=PIN0,
	.keypad_row[1].direction=GPIO_DIRECTION_OUTPUT,.keypad_row[1].logic=GPIO_LOGIC_LOW,
	.keypad_row[1].port=PORTD,.keypad_row[1].pin=PIN1,
	.keypad_row[2].direction=GPIO_DIRECTION_OUTPUT,.keypad_row[2].logic=GPIO_LOGIC_LOW,
	.keypad_row[2].port=PORTD,.keypad_row[2].pin=PIN2,
	.keypad_row[3].direction=GPIO_DIRECTION_OUTPUT,.keypad_row[3].logic=GPIO_LOGIC_LOW,
	.keypad_row[3].port=PORTD,.keypad_row[3].pin=PIN3,
	.keypad_column[0].direction=GPIO_DIRECTION_INPUT,.keypad_column[0].logic=GPIO_LOGIC_LOW,
	.keypad_column[0].port=PORTD,.keypad_column[0].pin=PIN4,
	.keypad_column[1].direction=GPIO_DIRECTION_INPUT,.keypad_column[1].logic=GPIO_LOGIC_LOW,
	.keypad_column[1].port=PORTD,.keypad_column[1].pin=PIN5,
	.keypad_column[2].direction=GPIO_DIRECTION_INPUT,.keypad_column[2].logic=GPIO_LOGIC_LOW,
	.keypad_column[2].port=PORTD,.keypad_column[2].pin=PIN6,
	.keypad_column[3].direction=GPIO_DIRECTION_INPUT,.keypad_column[3].logic=GPIO_LOGIC_LOW,
	.keypad_column[3].port=PORTD,.keypad_column[3].pin=PIN7,
};

void ECU_Init()
{
	lcd_4bit_initialize(&lcd1);
	keypad_initialize(&keypad1);
}