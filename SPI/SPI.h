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

#ifndef SPI_H_
#define SPI_H_

/* My Header Files which will need in any Project */
#include "Macros.h"
#include "Micro_Config.h"
#include "Std_Types.h"


typedef enum {
	SLAVE, MASTER, INPUT = 0, OUTPUT
} MODE_Config;

typedef enum {
	F_CPU_4, F_CPU_16, F_CPU_64, F_CPU_128, F_CPU_2, F_CPU_8, F_CPU_32
} FERQ;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MASTER_MODE						MASTER

#define F_SPI										F_CPU_4

#define SS_DIR									DDRB_REG.BITS.BIT4
#define MOSI_DIR								DDRB_REG.BITS.BIT5
#define MISO_DIR								DDRB_REG.BITS.BIT6
#define SCK_DIR									DDRB_REG.BITS.BIT7

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible to initialize SPI Master mode
 */
void SPI_initMaster(void);

/*
 * Function responsible to initialize SPI Slave mode
 */
void SPI_initSlave(void);

/*
 * Function responsible to send byte to another device .
 */
void SPI_sendByte(const uint8 data);

/*
 * Function responsible to receive byte from another device .
 */
uint8 SPI_recieveByte(void);

/*
 * Function responsible to send String for another device .
 */
void SPI_sendString(const uint8 *Str);

/*
 * Function responsible to receive String from another device .
 */
void SPI_receiveString(uint8 *const Str);

#endif /* SPI_H_ */
