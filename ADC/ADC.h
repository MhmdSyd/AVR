/******************************************************************************
 *
 * Module: ADC - Configuration
 *
 * File Name: ADC.h
 *
 * Description: File include all ADC Configuration Declaration and Prototype .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_
#include "Macros.h"
#include "Micro_Config.h"
#include "Std_Types.h"

/* ******************   Frequency ADC scaler ************* */
#define PRESCALER				F_CPU_8

typedef enum{
	F_CPU_2=1,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_64,F_CPU_128
}ADC_clock;

/* Select which bit store data in ADC  DATA Register ( first or last 10 bits ) */
#define DATA_LOCATION		LOW

/* Choose that active interrupt or polling to read ADC signal  */
#define INTERRUPT_STATE	0

/* Choose that use internal or external  reference voltage */
typedef enum{
	internal_Vref,external_AREF,Reserved,internal_256V
}ADC_Vref;

/* Choose that active interrupt or polling to read ADC signal  */
typedef enum{
	CLOSE,OPEN
}ADC_interrupt;

/* ADC Configuration Struct */
typedef struct{
	ADC_Vref Vref;
	ADC_interrupt interrupt;
	ADC_clock prescaler;
}ADC_Config;

/* *******************  AVR ADC Register  ********************* */
#define ADCSRA_REG 			(*(volatile REG * const ) 0x26)
#define ADMUX_REG 				(*(volatile REG * const ) 0x27)
#define ADCH_REG 				(*(volatile REG * const ) 0x25)
#define ADCL_REG 					(*(volatile REG * const ) 0x24)

/* ***************** 	ADC select reference bits *************** */
#define ADC_REF0					ADMUX_REG.BITS.BIT6
#define ADC_REF1					ADMUX_REG.BITS.BIT7

/* ******************  ADC interrupt enable bit ************** */
#define ADCIE							ADCSRA_REG.BITS.BIT3

#define ADCRP						ADMUX_REG.BITS.BIT5
/*******************************************************************************
 *                     LCD Functions deceleration                                   *
 *******************************************************************************/

/*
 * Function responsible to initialization ADC Module
 */
void ADC_init(ADC_Config *ptr);

/*
 * Function responsible to Read ADC signal from ADC Module
 */
void ADC_readChannel(uint8 ch_num, ADC_interrupt interruptState);

#endif /* ADC_H_ */
