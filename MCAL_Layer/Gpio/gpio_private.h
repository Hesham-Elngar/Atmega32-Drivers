/*
 * gpio_private.h
 *
 * Created: 7/24/2024 2:38:53 PM
 *  Author: Hesham Elngar
 */ 


#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_
#include "stdint.h"

#define PPORTA (*(volatile uint8_t*)0x3B)
#define PDDRA  (*(volatile uint8_t*)0x3A)
#define PPINA  (*(volatile uint8_t*)0x39)

#define PPORTB (*(volatile uint8_t*)0x38)
#define PDDRB  (*(volatile uint8_t*)0x37)
#define PPINB  (*(volatile uint8_t*)0x36)

#define PPORTC (*(volatile uint8_t*)0x35)
#define PDDRC  (*(volatile uint8_t*)0x34)
#define PPINC  (*(volatile uint8_t*)0x33)

#define PPORTD (*(volatile uint8_t*)0x32)
#define PDDRD  (*(volatile uint8_t*)0x31)
#define PPIND  (*(volatile uint8_t*)0x30)


#endif /* GPIO_PRIVATE_H_ */