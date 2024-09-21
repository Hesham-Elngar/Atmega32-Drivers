#ifndef EXTI_H_
#define EXTI_H_


#include "../Gpio/gpio.h"

#define GICR   (*(volatile uint8_t *)0x5B)
#define GIFR   (*(volatile uint8_t *)0x5A)
#define MCUCR  (*(volatile uint8_t *)0x55)
#define MCUCSR (*(volatile uint8_t *)0x54)
#define SREG   (*(volatile uint8_t *)0x5F)

#define MCUCR_ISC00 0
#define MCUCR_ISC01 1
#define MCUCR_ISC10 2
#define MCUCR_ISC11 3

#define MCUCSR_ISC2 6

#define GICR_INT0 6
#define GICR_INT1 7
#define GICR_INT2 5

#define GIFR_INTF0 6
#define GIFR_INTF1 7
#define GIFR_INTF2 5

#define SREG_GIE 7
#define EXTI_FALLING_EDGE_CFG 0
#define EXTI_RISING_EDGE_CFG 1

#define INT0_MAPPING (GPIO_Pin_Config){PIN2, PORTD, GPIO_DIRECTION_INPUT}
#define INT1_MAPPING (GPIO_Pin_Config){PIN3, PORTD, GPIO_DIRECTION_INPUT}
#define INT2_MAPPING (GPIO_Pin_Config){PIN2, PORTB, GPIO_DIRECTION_INPUT}

typedef enum
{
    EXT_INT0,
    EXT_INT1,
    EXT_INT2
} INT_SOURCE;

typedef struct
{
    void (*interrupt_Handler)(void);  // Pointer to the interrupt handler function
    GPIO_Pin_Config exti_pin;          // GPIO pin configuration
    uint8_t edge;                      // Edge configuration
    INT_SOURCE src;                   // Interrupt source
} EXTI_Pin_Config_t;

void EXTI_Init(EXTI_Pin_Config_t* pin_obj);

#endif /* EXTI_H_ */
