/*
 * ecu_init.h
 *
 * Created: 8/27/2024 10:35:18 PM
 *  Author: Hesham	
 */ 


#ifndef ECU_INIT_H_
#define ECU_INIT_H_

#include "../LCD/LCD.h"
#include "../Keypad/keypad.h"
#include "../DC_Motor/motor.h"
void ECU_Init();
extern Lcd_4bit lcd1;
extern Keypad_t keypad1;
extern dc_motor_t CAR_M1;
extern dc_motor_t CAR_M2;

#endif /* ECU_INIT_H_ */