#include <avr/io.h>
#include <util/delay.h>  // Include this for _delay_ms
#define F_CPU 8000000UL  // Define the CPU frequency
#include "MCAL_Layer/USART/usart.h"
// Define UART baud rate
#define BAUD 9600
#define MY_UBRR F_CPU/16/BAUD-1

void UART_Init(unsigned int ubrr)
{
	// Set baud rate
	UBRRH = (unsigned char)(ubrr >> 8);
	UBRRL = (unsigned char)ubrr;
	
	// Enable transmitter and receiver
	UCSRB = (1 << TXEN) | (1 << RXEN);
	
	// Set frame format: 8 data bits, 1 stop bit
	UCSRC = USART_Data_Size_8Bit | (USART_Stop_Bit_1Bit);
}

void UART_Transmit(char data)
{
	// Wait for empty transmit buffer
	while (!(UCSRA & (1 << UDRE)));
	
	// Put data into buffer, sends the data
	UDR = data;
}

char UART_Receive(void)
{
	// Wait for data to be received
	while (!(UCSRA & (1 << RXC)));
	
	// Get and return received data from buffer
	return UDR;
}

USART_Config_t uo={.Baud_Rate=9600,.Data_Size=USART_Data_Size_8Bit,.mechanism=POLLING_MECHANISM,
.parity_mode=USART_Parity_Mode_Disabled,.stop_bit=USART_Stop_Bit_1Bit,.mode=USART_Mode_Asynchronous};

int main(void)
{
	// Initialize UART
//  	UART_Init(MY_UBRR);
	MCAL_USART_Init(&uo);
	char received_data;
	UART_Transmit('A');
	while (1)
	{
		// Transmit a character
		
		received_data = MCAL_USART_ReciveData_Polling();
		MCAL_USART_TransmitData_Polling(received_data);
	}
	return 0;
}
