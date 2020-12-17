/******************************************************************************
 *
 * Module: EEPROM - Configuration
 *
 * File Name: EEPROM.h
 *
 * Description: File include all EEPROM Configuration Declaration and Prototype .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/


#ifndef EEPROM_H_
#define EEPROM_H_

/* My Header Files which will need in any Project */
#include "Std_Types.h"
#include  "Macros.h"
#include "Micro_Config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM_H_ */
