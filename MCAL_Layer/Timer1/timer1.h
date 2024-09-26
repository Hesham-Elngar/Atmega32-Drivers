/*
 * timer1.h
 *
 * Created: 8/27/2024 11:17:54 AM
 *  Author: Hesham
 */ 

#ifndef TIMER1_H_
#define TIMER1_H_

#include <stdint.h>

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
#define FOC1A  2
#define FOC1B  3
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
#define ICNC1  7


/* TIMSK - Timer/Counter Interrupt Mask Register */

#define TOIE0   0  // Timer/Counter0 Overflow Interrupt Enable
#define OCIE0   1  // Timer/Counter0 Output Compare Match Interrupt Enable
#define TOIE1   2  // Timer/Counter1 Overflow Interrupt Enable
#define OCIE1B  3  // Timer/Counter1 Output Compare B Match Interrupt Enable
#define OCIE1A  4  // Timer/Counter1 Output Compare A Match Interrupt Enable
#define TICIE1  5  // Timer/Counter1 Input Capture Interrupt Enable
#define TOIE2   6  // Timer/Counter2 Overflow Interrupt Enable
#define OCIE2   7  // Timer/Counter2 Output Compare Match Interrupt Enable



#define TIMER1_MODE_Normal                0
#define TIMER1_MODE_CTC                   1
#define TIMER1_MODE_Fast_PWM              2
#define TIMER1_MODE_ICU					  3

// Select Prescaler
#define TIMER1_PRESCALER_DIVIDED_BY_1     0b001
#define TIMER1_PRESCALER_DIVIDED_BY_8     0b010
#define TIMER1_PRESCALER_DIVIDED_BY_64    0b011
#define TIMER1_PRESCALER_DIVIDED_BY_256   0b100
#define TIMER1_PRESCALER_DIVIDED_BY_1024  0b101
// Timer1 prescaler for external clocking on T0 pin
#define TIMER1_PRESCALER_EXTERNAL_FALLING_EDGE   0b110
#define TIMER1_PRESCALER_EXTERNAL_RISING_EDGE    0b111

#define TIMER1_MODE_ICU_RISING_EDGE_CFG   1
#define TIMER1_MODE_ICU_FALLING_EDGE_CFG  0


typedef struct{
    void (*Timer1_InterruptHandler)(void);
	uint8_t mode;
    uint8_t prescaler;
	uint8_t edge;
	uint16_t preload_value;
} Timer1_Config_t;

void MCAL_Timer1_Init(Timer1_Config_t* Timer1_Obj);  // Add the missing semicolon
void MCAL_Timer1_Set_PWM_Duty_Cycle(uint8_t duty_cycle);
void MCAL_Timer1_CTC_mode_Write_Value(uint16_t value);
void MCAL_Timer1_ICU_Switch_Edge(uint8_t edge);
uint16_t MCAL_Timer1_Get_ICU();

#endif /* TIMER1_H_ */
