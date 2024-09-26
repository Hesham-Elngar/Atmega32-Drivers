/*
 * timer0.c
 *
 * Created: 8/26/2024 6:01:50 PM
 * Author: Hesham
 */ 

#include "timer0.h"
#include <avr/interrupt.h>

#define  WGM01 3    // Waveform Generation Mode bit 1
#define  WGM00 6    // Waveform Generation Mode bit 0
#define  COM01 5    // Compare Output Mode bit 1
#define  COM00 4    // Compare Output Mode bit 0

#define  OCIE0 1    // Output Compare Match Interrupt Enable
#define  TOIE0 0    // Timer Overflow Interrupt Enable

static void (*TIMER0_OVF_InerruptHanler)(void) = NULL;
static void (*TIMER0_CTC_InerruptHanler)(void) = NULL;

static void mode_routine(Timer0_Config_t* Timer0_Obj)
{
    TCCR0 &= ~(1 << WGM01 | 1 << WGM00); // Clear WGM bits to configure the mode
    switch (Timer0_Obj->mode) {
        case TIMER0_MODE_Normal:
            TIMSK |= (1 << TOIE0); // Enable overflow interrupt
            break;
        case TIMER0_MODE_PWM_Phase_Correct:
            TCCR0 |= (1 << WGM00);  // Set Phase Correct PWM mode
            break;
        case TIMER0_MODE_CTC:
            TCCR0 |= (1 << WGM01); // Set CTC mode
            TIMSK |= (1 << OCIE0); // Enable compare match interrupt
            break;
        case TIMER0_MODE_Fast_PWM:
            TCCR0 |= (1 << WGM00) | (1 << WGM01); // Set Fast PWM mode
            TCCR0 |= (1 << COM01); // Clear on compare match, set at TOP (non-inverting mode)
            break;
    }
}

static void set_prescaler(uint8_t clock_source)
{
    TCCR0 &= ~(0b111 << 0); // Clear prescaler bits
    TCCR0 |= clock_source;  // Set the new prescaler
}

void MCAL_Timer0_Init(Timer0_Config_t* Timer0_Obj)
{
    if (Timer0_Obj != NULL) {
        SREG |= (1 << SREG_GIE); // Enable global interrupts
        TIMER0_OVF_InerruptHanler = Timer0_Obj->Timer0_OVF_InterruptHandler;
        TIMER0_CTC_InerruptHanler = Timer0_Obj->Timer0_CTC_InterruptHandler;
        mode_routine(Timer0_Obj); // Set up the timer mode
        TCNT0 = Timer0_Obj->preload_value; // Preload the timer counter
        set_prescaler(Timer0_Obj->clock_source); // Set the clock source
    }
}

void MCAL_Timer0_CTC_mode_Write_Value(uint8_t value)
{
    OCR0 = value; // Write the value to the Output Compare Register
}

void MCAL_Timer0_Set_PWM_Duty_Cycle(uint8_t duty_cycle)
{
    if (duty_cycle > 100) {
        duty_cycle = 100; // Clamp duty cycle to a maximum of 100%
    }
    uint8_t pwm_value = (duty_cycle * 255) / 100; // Calculate the PWM value
    OCR0 = pwm_value; // Set the Output Compare Register value
}

// Interrupt Service Routines
ISR(TIMER0_OVF_vect)
{
    if (TIMER0_OVF_InerruptHanler != NULL) {
        TIMER0_OVF_InerruptHanler(); // Call the overflow interrupt handler
    }
}

ISR(TIMER0_COMP_vect)
{
    if (TIMER0_CTC_InerruptHanler != NULL) {
        TIMER0_CTC_InerruptHanler(); // Call the compare match interrupt handler
    }
}
