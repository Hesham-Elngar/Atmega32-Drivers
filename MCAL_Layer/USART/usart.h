/*
 * usart.h
 *
 * Created: 8/30/2024 8:44:32 PM
 *  Author: Hesham
 */ 

#ifndef USART_H_
#define USART_H_
#include <stdint.h>

#define UDR	   (*(uint8_t volatile*)0x2C)
#define UCSRA  (*(uint8_t volatile*)0x2B)
#define UCSRB  (*(uint8_t volatile*)0x2A)
#define UCSRC  (*(uint8_t volatile*)0x40)
#define UBRRH  (*(uint8_t volatile*)0x40)
#define UBRRL  (*(uint8_t volatile*)0x29)

#define UCSRA_RXC   (1<<7)	//Receive Complete
#define UCSRA_TXC   (1<<6)	//Transmit Complete
#define UCSRA_UDRE  (1<<5)	//USART Data Register Empty
#define UCSRA_FE	(1<<4)	// Frame Error
#define UCSRA_DOR   (1<<3)	//Data OverRun
#define UCSRA_PE    (1<<2)	//Parity Error
#define UCSRA_U2X   (1<<1)	// Double the USART Transmission Speed
#define UCSRA_MPCM   (1<<0)	/*asynchronous operation. Write this bit to zero when using syn-
one will reduce the divisor of the baud rate divider from 16 to 8 effectively doubling the transfer rate for asynchronous communication.*/

#define USART_RX_Complete_Interrupt_Enable() (UCSRB|=(1<<7))
#define USART_TX_Complete_Interrupt_Enable() (UCSRB|=(1<<6))
#define USART_Data_Register_Empty_Interrupt_Enable() (UCSRB|=(1<<5))
#define USART_RX_Enable() (UCSRB|=(1<<4))
#define USART_TX_Enable() (UCSRB|=(1<<3))


#define USED_MECHANISM POLLING_MECHANISM


// UCSRC Bits

// UCSRC or UBRRH 
#define UCSRC_SELCET (1<<7)
#define UBRRH_SELCET (0<<7)

//@mode_cfg
#define USART_Mode_Synchronous  (1<<6)
#define USART_Mode_Asynchronous (0<<6)

//@parity_mode_cfg
#define USART_Parity_Mode_Disabled	  (0b00<<4)
#define USART_Parity_Mode_Even_Parity (0b10<<4)
#define USART_Parity_Mode_Odd_Parity  (0b10<<4)

//@stop_bit_cfg
#define USART_Stop_Bit_1Bit (0<<3)
#define USART_Stop_Bit_2Bit (1<<3)

//@Data_Size_cfg
#define USART_Data_Size_5Bit  (0b00<<1)
#define USART_Data_Size_6Bit  (0b01<<1)
#define USART_Data_Size_7Bit  (0b10<<1)
#define USART_Data_Size_8Bit  (0b11<<1)
#define USART_Data_Size_9Bit  (0b11<<1); \
						      (UCSRB |= (1<<2))

								
//@clpol_cfg
#define USART_RisingTx_FallingRx (0<<0)
#define USART_FallingTx_RisingRx (1<<0)							


//@Usage
#define USART_USAGE_TX 1
#define USART_USAGE_RX 0

// @Baud_Rate_Prescalar
// #define Baud_Rate_Prescalar_divided_By_None  1
// #define Baud_Rate_Prescalar_divided_By_2	 2
// #define Baud_Rate_Prescalar_divided_By_8	 8
// #define Baud_Rate_Prescalar_divided_By_16	 16 

#define USART_U2X_Enable 1
#define USART_U2X_Disable 0

//@mechanism
#define INTERRUPT_MECHANISM 1
#define POLLING_MECHANISM	0


typedef struct{
	uint8_t mode; //asyn||sync @mode_cfg
	uint8_t parity_mode; //@parity_mode_cfg
	uint8_t stop_bit; //@stop_bit_cfg
	uint8_t Data_Size; //@Data_Size_cfg
	uint8_t mechanism; //@mechanism
	uint16_t Baud_Rate;
	uint16_t Baud_Rate_Prescalar; //@Baud_Rate_Prescalar
	uint8_t U2X_Enable; //Async mode
	uint8_t Clock_Polarity; //@clpol_cfg SyncOnly
#if USED_MECHANISM==INTERRUPT_MECHANISM
	void (*USART_TX_Complete_Interrupt_Handler)();
	void (*USART_TX_DR_Empty_Complete_Interrupt_Handler)();
	void (*USART_RX_Complete_Interrupt_Handler)();
#endif
}USART_Config_t;

void MCAL_USART_Init(USART_Config_t* usart_obj);
 #if USED_MECHANISM==POLLING_MECHANISM
void MCAL_USART_TransmitData_Polling(char Data);
uint8_t MCAL_USART_ReciveData_Polling();
void MCAL_USART_TransmitString_Polling(char* Data);
#endif
#if USED_MECHANISM==INTERRUPT_MECHANISM
void MCAL_USART_TransmitData_Interrupt(USART_Config_t* usart_obj,char* Data);
void MCAL_USART_ReciveData_Interrupt(USART_Config_t* usart_obj,char* Data);
#endif





#endif /* USART_H_ */