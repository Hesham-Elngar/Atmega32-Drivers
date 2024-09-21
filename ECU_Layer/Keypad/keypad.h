/* 
 * File:   keypad.h
 * Author: hesham
 *
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#include "../../MCAL_Layer/Gpio/gpio.h"

#define KEYPAD_ROWS    4
#define KEYPAD_COLUMNS 4

typedef struct{
    GPIO_Pin_Config keypad_row[KEYPAD_ROWS];
    GPIO_Pin_Config keypad_column[KEYPAD_COLUMNS];
}Keypad_t;

Return_Status keypad_initialize(Keypad_t* keypad);
Return_Status keypad_get_value(Keypad_t *keypad,uint8_t *value);


#endif	/* KEYPAD_H */

