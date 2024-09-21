#include "usart.h"
#include "../../MCAL_Layer/Gpio/gpio.h"
#define SREG   (*(volatile uint8_t *)0x5F)
#define SREG_GIE 7
#define URSEL 7

void (*P_USART_TX_Complete_Interrupt_Handler)();
void (*P_USART_TX_DR_Empty_Complete_Interrupt_Handler)();
void (*P_USART_RX_Complete_Interrupt_Handler)();

#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

#define F_CPU 8000000UL
void MCAL_USART_Init(USART_Config_t* usart_obj)
{

	// Disable global interrupts (optional: use only if critical section needed)
	SREG &= ~(1 << SREG_GIE);

	// Configure UCSRC (mode, clock polarity, stop bits, data size, and parity)
	UCSRC = (1 << URSEL) | usart_obj->mode | usart_obj->stop_bit | usart_obj->Data_Size | usart_obj->parity_mode;

	if (usart_obj->mode == USART_Mode_Synchronous)
	{
		UCSRC |= usart_obj->Clock_Polarity;
	}
	uint16_t ubrr;
	if (usart_obj->U2X_Enable == USART_U2X_Enable)
	{
		 ubrr =((F_CPU / (8UL * usart_obj->Baud_Rate)) - 1);
	}
	else
	{
		
		 ubrr = ((F_CPU / (16UL * usart_obj->Baud_Rate)) - 1);
	}
	// Set baud rate
	UBRRL = (unsigned char)ubrr;
	UBRRH = (unsigned char)(ubrr >> 8);
	// Enable TX and RX
	USART_TX_Enable();
	USART_RX_Enable();

	#if USED_MECHANISM == INTERRUPT_MECHANISM
	// Enable the TX and RX complete interrupts if in interrupt mode
	USART_TX_Complete_Interrupt_Enable();
	P_USART_TX_Complete_Interrupt_Handler = usart_obj->USART_TX_Complete_Interrupt_Handler;
	USART_RX_Complete_Interrupt_Enable();
	P_USART_RX_Complete_Interrupt_Handler = usart_obj->USART_RX_Complete_Interrupt_Handler;
	#endif

	// Enable global interrupts (optional: re-enable if previously disabled)
	SREG |= (1 << SREG_GIE);
}


void MCAL_USART_TransmitData_Polling(char Data)
{
	// Wait until the transmit buffer is empty
	while (!(UCSRA & UCSRA_UDRE));

	UDR = Data;
}
void MCAL_USART_TransmitString_Polling(char* Data)
{
	while (*Data)
	{
		// Wait until the transmit buffer is empty
		while (!(UCSRA & UCSRA_UDRE));

		// Put data into the buffer, which sends the data
		UDR = *Data++;
	}

}

uint8_t MCAL_USART_ReciveData_Polling()
{
	// Wait until the data is received
	while (!(UCSRA & UCSRA_RXC));

	// Get and return the received data from the buffer
	return UDR;
}
