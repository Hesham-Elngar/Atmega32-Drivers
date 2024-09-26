#include "timer1.h"
#include <stdlib.h>
#include <avr/interrupt.h>

static void (*TIMER1_OVF_InerruptHanler)(void) = NULL;
static void (*TIMER1_CTC_InerruptHanler)(void) = NULL;
static void (*TIMER1_ICU_InerruptHanler)(void) = NULL;

static void mode_handler(Timer1_Config_t* Timer1_Obj) {
	TCCR1A &= ~(1 << WGM11 | 1 << WGM10);  // Clear WGM bits
	TCCR1B &= ~(1 << WGM13 | 1 << WGM12);  // Clear WGM bits

	switch (Timer1_Obj->mode) {
		case TIMER1_MODE_Normal:
		TCCR1A &= ~((1 << COM1A1) | (1 << COM1A0));
		TIMSK |= (1 << TOIE1);  // Enable overflow interrupt
		TIMER1_OVF_InerruptHanler = Timer1_Obj->Timer1_InterruptHandler;
		break;

		case TIMER1_MODE_CTC:
		TIMSK |= (1 << OCIE1A);
		TIMER1_CTC_InerruptHanler = Timer1_Obj->Timer1_InterruptHandler;
		OCR1AH = (Timer1_Obj->preload_value >> 8);
		OCR1AL = (Timer1_Obj->preload_value & 0xFF);
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << COM1A1);
		break;

		case TIMER1_MODE_Fast_PWM:
		TCCR1A |= (1 << WGM10); // Fast PWM, non-inverting mode
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << COM1A1);
		break;

		case TIMER1_MODE_ICU:
		TCCR1A = 0x00;  // Clear TCCR1A
		TCCR1B |= (1 << ICNC1); // Enable noise canceler
		TCCR1B |= (1 << ICES1); // Set for rising edge
		TIMSK |= (1 << TICIE1); // Enable Input Capture interrupt
		TIMSK &= ~(1 << TOIE1); // Disable overflow interrupt
		DDRD &= ~(1 << PD6);      // Configure ICP1 (PD6) as input
		TIMER1_ICU_InerruptHanler = Timer1_Obj->Timer1_InterruptHandler;
		break;
	}
}

static void set_prescaler(uint8_t prescaler) {
	TCCR1B &= ~(0b111 << 0);  // Clear prescaler bits
	TCCR1B |= prescaler;      // Set prescaler bits based on user config
}

void MCAL_Timer1_Init(Timer1_Config_t* Timer1_Obj) {
	SREG |= (1 << 7); // Enable global interrupts
	mode_handler(Timer1_Obj);
	set_prescaler(Timer1_Obj->prescaler);
}

void MCAL_Timer1_CTC_mode_Write_Value(uint16_t value) {
	OCR1AH = (value >> 8);
	OCR1AL = (value & 0xFF);
}

void MCAL_Timer1_Set_PWM_Duty_Cycle(uint8_t duty_cycle) {
	uint16_t pwm_value = (duty_cycle * 255) / 100;
	OCR1AH = 0;  // Set high byte of OCR1A
	OCR1AL = pwm_value; // Set low byte of OCR1A
}

void MCAL_Timer1_ICU_Switch_Edge(uint8_t edge) {
	if (edge == TIMER1_MODE_ICU_FALLING_EDGE_CFG) {
		TCCR1B &= ~(1 << ICES1); // Set to falling edge
		} else {
		TCCR1B |= (1 << ICES1); // Set to rising edge
	}
}

uint16_t MCAL_Timer1_Get_ICU() {
	return ICR1;
}

// ISR Handlers
ISR(TIMER1_OVF_vect) {
	if (TIMER1_OVF_InerruptHanler != NULL) {
		TIMER1_OVF_InerruptHanler();
	}
}

ISR(TIMER1_COMPA_vect) {
	if (TIMER1_CTC_InerruptHanler != NULL) {
		TIMER1_CTC_InerruptHanler();
	}
}

ISR(TIMER1_CAPT_vect) {
	if (TIMER1_ICU_InerruptHanler != NULL) {
		TIMER1_ICU_InerruptHanler(); // Call the ICU handler
	}
}
