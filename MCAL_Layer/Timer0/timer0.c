/*
 * timer0.c
 *
 * Created: 8/26/2024 6:01:50 PM
 *  Author: Hesham
 */ 

#include "timer0.h"
#include <avr/interrupt.h>

#define  WGM01 3
#define  WGM00 6
#define  COM01 5
#define  COM00 4

#define  OCIE0 1
#define  TOIE0 0

static void (*TIMER0_OVF_InerruptHanler)(void) = NULL;
static void (*TIMER0_CTC_InerruptHanler)(void) = NULL;

static void mode_routine(Timer0_Config_t* Timer0_Obj)
{
	TCCR0 &= ~(1<<WGM01 | 1<<WGM00); // Clear WGM bits
	if(Timer0_Obj->mode==TIMER0_MODE_Normal)
	{
		TIMSK |= (1<<TOIE0); // Enable overflow interrupt
		TCCR0 |= (0<<WGM01) | (0<<WGM00); // Normal mode
	}
	else if(Timer0_Obj->mode==TIMER0_MODE_PWM_Phase_Correct)
	{
		TIMSK |= (1<<OCIE0); // Enable compare match interrupt
		TCCR0 |= (0<<WGM01) | (1<<WGM00); // Phase Correct PWM mode
	}
	else if(TIMER0_MODE_CTC==Timer0_Obj->mode)
	{
		TCCR0 |= (1<<WGM01) | (0<<WGM00); // CTC mode
		TCCR0 |= (1<<COM00);
	}
	else if(Timer0_Obj->mode==TIMER0_MODE_Fast_PWM)
	{
		TCCR0 |= (1<<WGM01) | (1<<WGM00); // Fast PWM mode
		TCCR0 |= (1<<COM01);
	}
}

static void set_prescaler(uint8_t clock_source)
{
	TCCR0 &= ~(0b111<<0); // Clear prescaler bits
	TCCR0 |= clock_source;
}

void MCAL_Timer0_Init(Timer0_Config_t* Timer0_Obj)
{
	if(Timer0_Obj!=NULL)
	{
		SREG |= (1<<SREG_GIE);
		TIMER0_OVF_InerruptHanler = Timer0_Obj->Timer0_OVF_InterruptHandler;
		TIMER0_CTC_InerruptHanler = Timer0_Obj->Timer0_CTC_InterruptHandler;
		mode_routine(Timer0_Obj);
		TCNT0=Timer0_Obj->preload_value;
		set_prescaler(Timer0_Obj->clock_source);		
	}
}

void MCAL_Timer0_CTC_mode_Write_Value(uint8_t value)
{
	OCR0 = value;
}

void MCAL_Timer0_Set_PWM_Duty_Cycle(uint8_t duty_cycle)
{
	// Clamp duty_cycle to be between 0 and 100
	if (duty_cycle > 100) {
		duty_cycle = 100;
	}

	// Calculate duty cycle as a value between 0 and 255
	uint8_t pwm_value = (duty_cycle * 255) / 100;
		OCR0 = pwm_value;
}


#define OCF0 1
#define TOV0 0

ISR(TIMER0_OVF_vect)
{
	if (TIMER0_OVF_InerruptHanler != NULL) TIMER0_OVF_InerruptHanler();
}
ISR(TIMER0_COMP_vect)
{
	if (TIMER0_CTC_InerruptHanler != NULL) TIMER0_CTC_InerruptHanler();
}
