/*
 * SPI.h
 *
 * Created: 1/24/2022 6:17:31 PM
 *  Author: Khaled Ali
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "../../LIB/Atmega32.h"
#include "../../LIB/BIT_Math.h"
#include "../../LIB/Typedef.h"
#include "SPI_cfg.h"

/* SPSR */
#define SPIF    7
#define WCOL    6
/* bits 5-1 reserved */
#define SPI2X   0

/* SPCR */
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1
#define SPR0    0

typedef enum{
	SPI_ERR,
	SPI_OK	
}SPI_ERR_STATE;

void SPI_u8Init(void);

void SPI_u8SendData(uint8_t data);

SPI_ERR_STATE SPI_u8ReceiveData(uint8_t* data);

void SPI_SetData(uint8_t data);
SPI_ERR_STATE SPI_u8SendString(uint8_t* str);
SPI_ERR_STATE SPI_u8ReceiveString(uint8_t* str, uint8_t stop_char);

#endif /* SPI_H_ */