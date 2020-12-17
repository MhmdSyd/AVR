/******************************************************************************
 *
 * Module: I2C - Configuration
 *
 * File Name: I2C.h
 *
 * Description: File include all I2C Configuration  Functions Definitions   .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

/*                                 	I2C Header File                                                      */
#include "I2C.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function responsible to initialize I2C
 */
void I2C_init(void) {

	/* Select Bit Rate: 400 kbps   */
	TWBR = TWBR_VALUE;
	TWSR = TWSR_VALUE;

	TWAR = 0x02;		/* Select device address */

	SET_BIT(TWCR, TWEN); 	/* enable I2C */
}

/*
 * Function responsible to send START bit to TWI BUS
 */
void I2C_start(void) {

	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the START bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT));

}

/*
 * Function responsible to send STOP bit to TWI BUS .
 */
void I2C_stop(void) {
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the STOP bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);

}

/*
 * Function responsible to send data to TWI BUS .
 */
void I2C_write(uint8 data) {
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT));

}

/*
 * Function responsible to read data from TWI BUS & request more data .
 */
uint8 I2C_readWith_ACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT));
	/* Read Data */
	return TWDR;

}

/*
 * Function responsible to read data from TWI BUS & request stop data transfer .
 */
uint8 I2C_readWith_NACK(void) {
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT));
	/* Read Data */
	return TWDR;
}

/*
 * Function responsible to read status register .
 */
uint8 I2C_getStatus(void) {
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}

