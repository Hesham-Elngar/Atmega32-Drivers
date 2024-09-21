/*
 * timer0.h
 *
 * Created: 8/26/2024 6:02:04 PM
 *  Author: Hesham
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>
#include <stdlib.h>

#define OCR0   (*(volatile uint8_t *)0x5C)
#define TCNT0  (*(volatile uint8_t *)0x52)
#define TCCR0  (*(volatile uint8_t *)0x53)
#define TIFR   (*(volatile uint8_t *)0x58)
#define TIMSK  (*(volatile uint8_t *)0x59)
#define SREG   (*(volatile uint8_t *)0x5F)

#define SREG_GIE 7

//Select Prescaler => Bit 2:0 – CS02:0
#define TIMER0_PRESCALER_DIVIDED_BY_1   0b001
#define TIMER0_PRESCALER_DIVIDED_BY_8   0b010
#define TIMER0_PRESCALER_DIVIDED_BY_64  0b011
#define TIMER0_PRESCALER_DIVIDED_BY_256 0b100
#define TIMER0_PRESCALER_DIVIDED_BY_1024 0b101
// Timer0 prescaler for external clocking on T0 pin
#define TIMER0_PRESCALER_EXTERNAL_FALLING_EDGE   0b110
#define TIMER0_PRESCALER_EXTERNAL_RISING_EDGE    0b111

// select mode  Bit 6, 3 – WGM01:0
#define TIMER0_MODE_Normal			  0
#define TIMER0_MODE_PWM_Phase_Correct 1
#define TIMER0_MODE_CTC      		  2
#define TIMER0_MODE_Fast_PWM		  3


typedef struct
{
	void (*Timer0_OVF_InterruptHandler)(void);
	void (*Timer0_CTC_InterruptHandler)(void);
	uint8_t mode;
	uint8_t clock_source:3; //Bit 2:0 – CS02:0
	uint8_t preload_value;
}Timer0_Config_t;

void MCAL_Timer0_Init(Timer0_Config_t* Timer0_Obj);
void MCAL_Timer0_CTC_mode_Write_Value(uint8_t value);
void MCAL_Timer0_Set_PWM_Duty_Cycle(uint8_t duty_cycle);


#endif /* TIMER0_H_ */
