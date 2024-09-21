/*
 * timer1.h
 *
 * Created: 8/27/2024 11:17:54 AM
 *  Author: Hesham
 */ 

#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

#define TCCR1A (*(volatile uint8_t*)0x4F)
#define TCCR1B (*(volatile uint8_t*)0x4E)
#define TCNT1H (*(volatile uint8_t*)0x4D)
#define TCNT1L (*(volatile uint8_t*)0x4C)
#define OCR1AH (*(volatile uint8_t*)0x4B)
#define OCR1AL (*(volatile uint8_t*)0x4A)
#define OCR1BH (*(volatile uint8_t*)0x49)
#define OCR1BL (*(volatile uint8_t*)0x48)
#define ICR1H  (*(volatile uint8_t*)0x47)
#define ICR1L  (*(volatile uint8_t*)0x46)
#define TIMSK  (*(volatile uint8_t*)0x59)
#define SREG   (*(volatile uint8_t*)0x5F)

#define SREG_GIE (1<<7)  // Global Interrupt Enable

// TCCR1A Bit Definitions
#define WGM10  0
#define WGM11  1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

// TCCR1B Bit Definitions
#define CS10   0
#define CS11   1
#define CS12   2
#define WGM12  3
#define WGM13  4
#define ICES1  6
#define CNC1   7

// Select Prescaler
#define TIMER1_PRESCALER_DIVIDED_BY_1     0b001
#define TIMER1_PRESCALER_DIVIDED_BY_8     0b010
#define TIMER1_PRESCALER_DIVIDED_BY_64    0b011
#define TIMER1_PRESCALER_DIVIDED_BY_256   0b100
#define TIMER1_PRESCALER_DIVIDED_BY_1024  0b101

// Timer Modes
#define TIMER1_MODE_Normal                0
#define TIMER1_MODE_CTC                   1
#define TIMER1_MODE_PWM_Phase_Correct     2
#define TIMER1_MODE_Fast_PWM              3

// ICU Edge Select
#define TIMER1_MODE_ICU_RISING_EDGE_CFG   (1<<ICES1)
#define TIMER1_MODE_ICU_FALLING_EDGE_CFG  (0<<ICES1)

typedef struct
{
    void (*Timer1_InterruptHandler)(void);
    uint8_t mode;
    uint8_t prescaler:3;
    uint16_t preload_value;
    uint16_t pwm_value;
    uint8_t Icu_Edge;
} Timer1_Config_t;

void MCAL_Timer1_Init(Timer1_Config_t* Timer1_Obj);
void MCAL_Timer1_CTC_mode_Write_Value(uint16_t value);
void MCAL_Timer1_Set_PWM_Duty_Cycle(uint16_t duty_cycle);
uint16_t MCAL_Timer1_Get_ICU(Timer1_Config_t* Timer1_Obj);

#endif /* TIMER1_H_ */
