/*
 * main2.c
 *
 * Created: 1/24/2022 7:33:43 PM
 *  Author: Khaled Ali
 */ 
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/TIMER/TIMER0.h"
uint8_t data[20];
void App_Master(void)
{
	DIO_u8SetPinDirection(PORTD, PIN0, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTD, PIN1, OUTPUT_PIN);
	DIO_u8SetPinDirection(PORTB, PIN4, OUTPUT_PIN);
	DIO_u8SetPinDirection(PORTB, PIN5, OUTPUT_PIN);
	DIO_u8SetPinDirection(PORTB, PIN6, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTB, PIN7, OUTPUT_PIN);
	UART_u8Init(9600);
	SPI_u8Init();
	while (1)
	{
		UART_u8ReceiveString(data, '\r');
		DIO_u8SetPinData(PORTB, PIN4, LOW);
		SPI_u8SendString(data);
		DIO_u8SetPinData(PORTB, PIN4, HIGH);		
	}
}