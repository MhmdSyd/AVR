/******************************************************************************
 *
 * Module: I2C - Configuration
 *
 * File Name: I2C.h
 *
 * Description: File include all I2C Configuration Declaration and Prototype .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

/* My Header Files which will need in any Project */
#include "Macros.h"
#include "Micro_Config.h"
#include "Std_Types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

 /* Choose Bit Rate: 400 kbps  or 100 kbps or 3.4 MHZ */
#define SCL						 								400000
#define TWSR_VALUE										0
#define TWBR_VALUE										2

/* I2C Status Bits in the TWSR Register */
#define TW_START        									0x08 				/*start has been sent */
#define TW_REP_START     							0x10 				/* repeated start */
/* Master transmit ( slave address + Write request ) to slave + Ack received from slave */
#define TW_MT_SLA_W_ACK  						0x18
/* Master transmit ( slave address + Read request ) to slave + Ack received from slave */
#define TW_MT_SLA_R_ACK  							0x40
/* Master transmit data and ACK has been received from Slave.*/
#define TW_MT_DATA_ACK   						0x28
/* Master received data and send ACK to slave */
#define TW_MR_DATA_ACK   						0x50
/* Master received data but doesn't send ACK to slave */
#define TW_MR_DATA_NACK  						0x58


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible to initialize I2C
 */
void I2C_init(void);

/*
 * Function responsible to send START bit to TWI BUS
 */
void I2C_start(void);

/*
 * Function responsible to send STOP bit to TWI BUS .
 */
void I2C_stop(void);

/*
 * Function responsible to send data to TWI BUS .
 */
void I2C_write(uint8 data);

/*
 * Function responsible to read data from TWI BUS & request more data .
 */
uint8 I2C_readWith_ACK(void);

/*
 * Function responsible to read data from TWI BUS & request stop data transfer .
 */
uint8 I2C_readWith_NACK(void);

/*
 * Function responsible to read status register .
 */
uint8 I2C_getStatus(void);

#endif /* I2C_H_ */
