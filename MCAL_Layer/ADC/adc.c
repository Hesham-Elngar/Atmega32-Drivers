/*
 * adc.c
 *
 * Created: 9/1/2024 4:54:06 AM
 *  Author: Hesham
 */ 
#include "adc.h"
#include <stdlib.h>
#include <avr/interrupt.h>
#define SREG   (*(volatile uint8_t *)0x5F)
#define SREG_GIE 7

void (*P_ADC_InterruptHandler)(void);

void MCAL_ADC_Init(ADC_Config_t* adc_obj)
{
	if (adc_obj!=NULL)
	{
		ADCSRA |= ADC_ENABLE;
		ADCSRA |= ADC_AutoTrigger_Enable;
		ADCSRA |= adc_obj->prescaler;
		ADMUX  |= adc_obj->Adjust_Result;
		ADMUX  |= adc_obj->analog_channel;
		ADMUX  |= adc_obj->voltage_reference;
		if (adc_obj->mechanism==INTERRUPT_MECHANISM)
		{
			SREG   |= (1<<SREG_GIE);
			ADCSRA |= ADC_Interrupt_Enable;
			P_ADC_InterruptHandler=adc_obj->ADC_InterruptHandler;
		}
	}
}
void MCAL_ADC_Start_Conversion(void)
{
	ADCSRA |= ADC_Start_Conversion;	
}
uint16_t MCAL_ADC_Get_Conversion_Result_Polling(void)
{
	uint16_t value=0;
		while(!(ADCSRA&ADC_Interrupt_Flag));
		value  =   (uint8_t)ADCL;
		value  |=  (uint8_t)(ADCH<<8); //Right-Justified Mode
		ADCSRA |= ADC_Interrupt_Flag;
	return value;
}

ISR(ADC_vect)
{
	if (P_ADC_InterruptHandler != NULL)
	{
		P_ADC_InterruptHandler();  // Call the user-defined interrupt handler
	}
}