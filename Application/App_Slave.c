/*
 * UART_Driver.c
 *
 * Created: 1/24/2022 12:19:11 AM
 * Author : Khaled Ali
 */ 
#include "../MCAL/SPI/SPI.h"
#include "../MCAL/UART/UART.h"
#include "../MCAL/DIO/DIO.h"
uint8_t data[255];
void App_Slave(void)
{
	DIO_u8SetPinDirection(PORTD, PIN0, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTD, PIN1, OUTPUT_PIN);
	DIO_u8SetPinDirection(PORTB, PIN4, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTB, PIN5, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTB, PIN6, OUTPUT_PIN);
	DIO_u8SetPinDirection(PORTB, PIN7, INPUT_PIN_NO_PULLUP);
	UART_u8Init(9600);
	SPI_u8Init();
	uint8_t start;
    while (1) 
    {
		DIO_u8GetPinData(PORTB, PIN4, &start);
		if(start == 0){
			SPI_u8ReceiveString(data, '.');
			UART_u8SendString(data);
		}
    }
}

