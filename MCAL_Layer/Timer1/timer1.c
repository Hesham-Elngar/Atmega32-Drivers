/*
 * timer1.c
 *
 * Created: 8/27/2024 11:18:17 AM
 *  Author: Hesham
 */ 
#include "timer1.h"

#define TOIE1  (1<<2)
#define OCIE1B (1<<3)
#define OCIE1A (1<<4)
#define TICIE1 (1<<5)

static void (*TIMER1_OVF_InerruptHanler)(void) = NULL;
static void (*TIMER1_CTC_InerruptHanler)(void) = NULL;
static void (*TIMER1_ICU_InerruptHanler)(void) = NULL;

static void set_prescaler(uint8_t prescaler)
{
    TCCR1B &= ~(0b111<<0);  // Clear prescaler bits
    TCCR1B |= prescaler;     // Set prescaler bits based on user config
}

static void mode_routine(Timer1_Config_t* Timer1_Obj)
{
	if (Timer1_Obj == NULL) return; 
    TCCR1A &= ~(1<<WGM11 | 1<<WGM10);  // Clear WGM bits
    TCCR1B &= ~(1<<WGM13 | 1<<WGM12);  // Clear WGM bits

    switch(Timer1_Obj->mode)
    {
        case TIMER1_MODE_Normal:
            TIMSK |= TOIE1;  // Enable overflow interrupt
            Timer1_Obj->Timer1_InterruptHandler = TIMER1_OVF_InerruptHanler;
            break;
        
        case TIMER1_MODE_CTC:
            TIMSK |= OCIE1A;  // Enable compare match interrupt
            Timer1_Obj->Timer1_InterruptHandler = TIMER1_CTC_InerruptHanler;
            break;
        
        case TIMER1_MODE_PWM_Phase_Correct:
            TCCR1A |= (1<<WGM11);  // Set Phase Correct PWM mode
            TCCR1B |= (1<<WGM13);  // ICR1 as TOP
            MCAL_Timer1_Set_PWM_Duty_Cycle(Timer1_Obj->pwm_value);  
            break;
        
        case TIMER1_MODE_Fast_PWM:
            TCCR1A |= (1<<WGM11) | (1<<WGM10);  // Set Fast PWM mode
            TCCR1B |= (1<<WGM13) | (1<<WGM12);  // OCR1A as TOP
            MCAL_Timer1_Set_PWM_Duty_Cycle(Timer1_Obj->pwm_value);  
            break;
    }
}

void MCAL_Timer1_Init(Timer1_Config_t* Timer1_Obj)
{
	if (Timer1_Obj == NULL) return; 
    mode_routine(Timer1_Obj);
    set_prescaler(Timer1_Obj->prescaler);  
    TCNT1H = (Timer1_Obj->preload_value >> 8);
    TCNT1L = (Timer1_Obj->preload_value & 0xFF);
}

void MCAL_Timer1_CTC_mode_Write_Value(uint16_t value)
{
    OCR1AH = (value >> 8);
    OCR1AL = (value & 0xFF);
}

void MCAL_Timer1_Set_PWM_Duty_Cycle(uint16_t duty_cycle)
{
	
	// Convert percentage to 16-bit value for Timer1
	uint16_t pwm_value = (duty_cycle * 65535) / 100;

	// Set the PWM duty cycle in the corresponding registers
	OCR1AH = (pwm_value >> 8);  // Set high byte of OCR1A
	OCR1AL = (pwm_value & 0xFF); // Set low byte of OCR1A
}

void MCAL_Timer1_Set_ICU(Timer1_Config_t* Timer1_Obj)
{
	if (Timer1_Obj == NULL) return; 
    TIMSK |= TICIE1;  // Enable ICU interrupt
    TCCR1B |= Timer1_Obj->Icu_Edge;  // Set ICU edge detection
}

uint16_t MCAL_Timer1_Get_ICU(Timer1_Config_t* Timer1_Obj)
{
	if (Timer1_Obj == NULL) return 0; 
    uint16_t result = (uint16_t)ICR1H << 8;  // Shift high byte
    result |= ICR1L;  // Combine with low byte
    return result;
}

// ISR Handlers
ISR(TIMER1_OVF_vect)
{
    if (TIMER1_OVF_InerruptHanler != NULL) 
        TIMER1_OVF_InerruptHanler();
}

ISR(TIMER1_COMPA_vect)
{
    if (TIMER1_CTC_InerruptHanler != NULL) 
        TIMER1_CTC_InerruptHanler();
}

ISR(TIMER1_CAPT_vect)
{
    if (TIMER1_ICU_InerruptHanler != NULL) 
        TIMER1_ICU_InerruptHanler();
}
