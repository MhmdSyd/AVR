/******************************************************************************
 *
 * Module: EEPROM - Configuration
 *
 * File Name: EEPROM.h
 *
 * Description: File include all EEPROM Configuration  Functions Definitions   .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/


/*                                 	 Header File                                                      */
#include "I2C.h"
#include "EEPROM.h"

void EEPROM_init(void){

	I2C_init(); /* initialize I2C Module */

}

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){

	I2C_start();
	if(I2C_getStatus() != TW_START)
		return ERROR;

	I2C_write((uint8) ((0xA0) | ((u16addr & 0x0700) >> 7)));
	if(I2C_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	I2C_write((uint8)(u16addr));
	if(I2C_getStatus() != TW_MT_DATA_ACK)
		return ERROR;


	I2C_write((uint8)(u8data));
	if(I2C_getStatus() != TW_MT_DATA_ACK)
		return ERROR;

	I2C_stop();

	return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	I2C_start();
	if(I2C_getStatus() != TW_START)
		return ERROR;

    I2C_write((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (I2C_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    I2C_write((uint8)(u16addr));
    if (I2C_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

	I2C_start();
	if (I2C_getStatus() != TW_REP_START)
		return ERROR;

	I2C_write((uint8) ((0xA0) | ((u16addr & 0x0701) >> 7)));
	if (I2C_getStatus() != TW_MT_SLA_W_ACK)
		return ERROR;

	I2C_write((uint8)(u16addr));
	if(I2C_getStatus() != TW_MT_SLA_R_ACK)
		return ERROR;


	*u8data = I2C_readWith_ACK();
	if(I2C_getStatus() != TW_MR_DATA_NACK)
		return ERROR;

	I2C_stop();

	return SUCCESS;
}
