/*
 * SPI.c
 *
 * Created: 1/24/2022 6:17:40 PM
 *  Author: Khaled Ali
 */ 
#include "SPI.h"

#include "../TIMER/TIMER0.h"

void SPI_u8Init(void){
	if(SPI_DATA_ORDER == LSB_FIRST){
		SET_BIT(SPCR_REG, DORD);
	}
	else{
		CLR_BIT(SPCR_REG, DORD);
	}
	if(SPI_MODE == MASTER){
		SET_BIT(SPCR_REG, MSTR);
	}
	else{
		CLR_BIT(SPCR_REG, MSTR);
	}
	
	if(SPI_PRESCALER == 4){
		CLR_BIT(SPCR_REG, SPR1);
		CLR_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 16){
		CLR_BIT(SPCR_REG, SPR1);
		SET_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 64){
		SET_BIT(SPCR_REG, SPR1);
		CLR_BIT(SPCR_REG, SPR0);
	}
	else if(SPI_PRESCALER == 128){
		SET_BIT(SPCR_REG, SPR1);
		SET_BIT(SPCR_REG, SPR0);
	}
	SET_BIT(SPCR_REG, SPE);
}

void SPI_u8SendData(uint8_t data){
	SPDR_REG = data;
	uint8_t volatile buffer;
	while(GET_BIT(SPSR_REG, SPIF) == 0);
	//Flush the buffer
	buffer = SPDR_REG;
}

SPI_ERR_STATE SPI_u8ReceiveData(uint8_t* data){
	SPI_ERR_STATE u8Status = SPI_OK;
	if(data == NULL){
		u8Status = SPI_ERR;
	}
	else{
		if(SPI_MODE == MASTER){
			SPDR_REG = 0xFF; //Initiate the Clock
		}
		while(GET_BIT(SPSR_REG, SPIF) == 0);
		*data = SPDR_REG;
	}
	return u8Status;
}

void SPI_SetData(uint8_t data){
	SPDR_REG = data;
}

SPI_ERR_STATE SPI_u8SendString(uint8_t* str){
	SPI_ERR_STATE u8Status = SPI_OK;
	if(str == NULL){
		u8Status = SPI_ERR;
	}
	else{
		uint8_t* itr = str;
		while(*itr != '\0'){
			SPI_u8SendData(*itr);
			TIMER0_u8PollingDelay(10);
			itr++;
		}
	}
	return u8Status;
}

SPI_ERR_STATE SPI_u8ReceiveString(uint8_t* str, uint8_t stop_char){
	SPI_ERR_STATE u8Status = SPI_OK;
	if(str == NULL){
		u8Status = SPI_OK;
	}
	else{
		uint8_t chr, i = 0;
		u8Status = SPI_u8ReceiveData(&chr);
		TIMER0_u8PollingDelay(10);
		while(chr != stop_char && u8Status == SPI_OK){
			str[i] = chr;
			u8Status = SPI_u8ReceiveData(&chr);
			TIMER0_u8PollingDelay(10);
			i++;
		}
		str[i] = '\0';
	}
	return u8Status;
}