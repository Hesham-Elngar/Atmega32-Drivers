/*
 * gpio.h
 *
 * Created: 7/24/2024 2:38:32 PM
 *  Author: Hesham Elngar
 */ 


#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000UL
#include <util/delay.h>

#define SET_BIT(REG, BIT)    (REG |= (1 << (BIT)))
#define CLR_BIT(REG, BIT)    (REG &= ~(1 << (BIT)))
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << (BIT)))
#define READ_BIT(REG, BIT)   ((REG >> (BIT)) & 1)

#define  PORTA 0
#define  PORTB 1
#define  PORTC 2
#define  PORTD 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7

#define  GPIO_LOGIC_LOW  0
#define  GPIO_LOGIC_HIGH 1

#define  GPIO_DIRECTION_INPUT  0
#define  GPIO_DIRECTION_OUTPUT 1

typedef enum{
	R_NOK,
	R_OK
	}Return_Status;

typedef struct{
	uint8_t pin:3;
	uint8_t port:2;
	uint8_t direction:1;
	uint8_t logic:1;
	}GPIO_Pin_Config;

Return_Status GPIO_Pin_Init(GPIO_Pin_Config* pin);
Return_Status GPIO_Set_Pin_Direction(GPIO_Pin_Config* pin,uint8_t direction);
Return_Status GPIO_Get_Pin_Direction(GPIO_Pin_Config* pin,uint8_t* direction);
Return_Status GPIO_Set_Pin_Logic(GPIO_Pin_Config* pin,uint8_t logic);
Return_Status GPIO_Get_Pin_Logic(GPIO_Pin_Config* pin,uint8_t* logic);
Return_Status GPIO_Active_Pin_PullUp_Resistor(GPIO_Pin_Config* pin);
Return_Status GPIO_DeActive_Pin_PullUp_Resistor(GPIO_Pin_Config* pin);
Return_Status GPIO_Toggle_Pin(GPIO_Pin_Config* pin);

Return_Status GPIO_Set_Port_Direction(uint8_t port,uint8_t direction);
Return_Status GPIO_Get_Port_Direction(uint8_t port,uint8_t* direction);
Return_Status GPIO_Set_Port_Logic(uint8_t port,uint8_t logic);
Return_Status GPIO_Get_Port_Logic(uint8_t port,uint8_t* logic);
Return_Status GPIO_Active_Port_PullUp_Resistor(uint8_t port);
Return_Status GPIO_DeActive_Port_PullUp_Resistor(uint8_t port);
Return_Status GPIO_Toggle_Port(uint8_t port);


#endif /* GPIO_H_ */