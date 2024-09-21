/*
 * EXTI.c
 *
 * Created: 8/14/2024 2:42:57 AM
 *  Author: Hehsam
 */ 


#include <avr/interrupt.h>
#include <stdlib.h>

void __attribute__((interrupt))INT0_ISR(void) ;
void __attribute__((interrupt))INT1_ISR(void) ;
void __attribute__((interrupt))INT2_ISR(void) ;

void (*Gp_int_handler[3])(void)={NULL};

#include "EXTI.h"

static void select_edge(EXTI_Pin_Config_t* pin_obj)
{
	if(pin_obj->src==EXT_INT0)
	{
		if(pin_obj->edge==EXTI_RISING_EDGE_CFG)
		{
			SET_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
		}
		else if (pin_obj->edge==EXTI_FALLING_EDGE_CFG)
		{
			CLR_BIT(MCUCR,MCUCR_ISC00);
			SET_BIT(MCUCR,MCUCR_ISC01);
		}
	}
	else if(pin_obj->src==EXT_INT1)
	{
		if(pin_obj->edge==EXTI_RISING_EDGE_CFG)
		{
			SET_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
		}
		else if (pin_obj->edge==EXTI_FALLING_EDGE_CFG)
		{
			CLR_BIT(MCUCR,MCUCR_ISC10);
			SET_BIT(MCUCR,MCUCR_ISC11);
		}
	}
	else if(pin_obj->src==EXT_INT2)
	{
		if(pin_obj->edge==EXTI_RISING_EDGE_CFG)
		{
			SET_BIT(MCUCSR,MCUCSR_ISC2);
		}
		else if (pin_obj->edge==EXTI_FALLING_EDGE_CFG)
		{
			CLR_BIT(MCUCSR,MCUCSR_ISC2);
		}
	}
}


static void enable_interrupt(EXTI_Pin_Config_t* pin_obj)
{
	SET_BIT(SREG, SREG_GIE);
	switch(pin_obj->src)
	{
		case EXT_INT0: SET_BIT(GICR, GICR_INT0); break;
		case EXT_INT1: SET_BIT(GICR, GICR_INT1); break;
		case EXT_INT2: SET_BIT(GICR, GICR_INT2); break;
	}
}


void EXTI_Init(EXTI_Pin_Config_t* pin_obj)
{
	select_edge(pin_obj);
	enable_interrupt(pin_obj);
	Gp_int_handler[pin_obj->src]=pin_obj->interrupt_Handler;
}

ISR(INT0_vect) {
	if (Gp_int_handler[EXT_INT0])
	{
		Gp_int_handler[EXT_INT0]();
	}
}

ISR(INT1_vect) {
	if (Gp_int_handler[EXT_INT1])
	{
		Gp_int_handler[EXT_INT1]();
	}
}

ISR(INT2_vect) {
	if (Gp_int_handler[EXT_INT2])
	{
		Gp_int_handler[EXT_INT2]();
	}
}