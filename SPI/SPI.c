/******************************************************************************
 *
 * Module: SPI - Configuration
 *
 * File Name: SPI.h
 *
 * Description: File include all SPI Configuration Declaration and Prototype .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

/*                                 	SPI Header File                                                      */
#include "SPI.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function responsible to initialize SPI Master mode
 */
void SPI_initMaster(void) {

	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	SS_DIR = OUTPUT;
	MOSI_DIR = OUTPUT;
	MISO_DIR = INPUT;
	SCK_DIR = OUTPUT;

	SET_BIT(SPCR, MSTR); /*  select master mode */
	SET_BIT(SPCR, SPE); /* ENABLE SPI */

	/* Select send data Frequency  */
	SPCR = (SPCR & 0xFC) | (F_SPI & 0x03);
	SPSR = (SPSR & 0xFE) | ((F_SPI >> 2) & 0x03);

}

/*
 * Function responsible to initialize SPI Slave mode
 */
void SPI_initSlave(void) {
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	SS_DIR = INPUT;
	MOSI_DIR = INPUT;
	MISO_DIR = OUTPUT;
	SCK_DIR = INPUT;
	SET_BIT(SPCR, SPE); /* ENABLE SPI */

	/* Select send data Frequency  */
	SPCR = (SPCR & 0xFC) | (F_SPI & 0x03);
	SPSR = (SPSR & 0xFE) | ((F_SPI >> 2) & 0x03);
}

/*
 * Function responsible to send byte to another device .
 */
void SPI_sendByte(uint8 data) {

	SPDR = data; //send data by SPI
	while (BIT_IS_CLEAR(SPSR, SPIF)) {
	} //wait until SPI interrupt flag=1 (data is sent correctly)
}

/*
 * Function responsible to receive byte from another device .
 */
uint8 SPI_receiveByte(void) {
	while (BIT_IS_CLEAR(SPSR, SPIF)) {
	} //wait until SPI interrupt flag=1(data is receive correctly)
	return SPDR; //return the received byte from SPI data register
}

/*
 * Function responsible to send String for another device .
 */
void SPI_sendString(const uint8 *Str) {
	uint8 i = 0;
	while (Str[i] != '\0') {
		SPI_sendByte(Str[i]);
		i++;
	}
	SPI_sendByte('#');

}

/*
 * Function responsible to receive String from another device .
 */
void SPI_receiveString(uint8 *const Str) {
	uint8 i = 0;
	do {
		Str[i] = SPI_receiveByte();
	} while (Str[i++] != '#');
	Str[--i] = '\0';
}

