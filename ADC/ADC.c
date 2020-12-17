/******************************************************************************
 *
 * Module: ADC - Configuration
 *
 * File Name: ADC.c
 *
 * Description: File include all ADC Configuration Function .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/
/*                                 	ADC Header File                                                      */

#include "ADC.h"

volatile sint16 g_adcResult = 0;

/*******************************************************************************
 *                    			   ADC Functions definition                                   *
 *******************************************************************************/
/*
 * Function responsible to initialization ADC Module
 */
void ADC_init(ADC_Config *ptr) {
/* ***************** 	Choose ADC Reference *************** */
	ADMUX = (ADMUX & 0x3F) | (ptr->Vref <<6);

/* Select which bit store data in ADC  DATA Register ( first or last 10 bits ) */
	ADCRP = DATA_LOCATION;

	SET_BIT(ADCSRA, ADEN); /* enable ADC  */

	ADCIE = ptr->interrupt; /* Choose that active interrupt or polling to read ADC signal  */

	ADCSRA = (ADCSRA & 0xF8) | (ptr->prescaler & 0x07); /* Select prescaler of ADC frequency */

	return;
}

/*
 * Function responsible to Read ADC signal from ADC Module
 */
void ADC_readChannel(uint8 ch_num, ADC_interrupt interruptState) {

	/* select pin which need to read analog signal */
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x1F);

	SET_BIT(ADCSRA, ADSC); /* start conversion  analog signal */

	if( interruptState == CLOSE)	{	/* at polling Mode */

	while(BIT_IS_SET(ADCSRA, ADIF));	/* wait until flag =1 */

	SET_BIT(ADCSRA, ADIF); 	/* clear flag by set  1 */

	g_adcResult = ADC;		/* read ADC convert data */
	}
	return;
}

ISR(ADC_vect){
	g_adcResult = ADC;	/* read ADC convert data at interrupt mode */
}
