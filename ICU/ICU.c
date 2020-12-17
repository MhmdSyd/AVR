/******************************************************************************
 *
 * Module: ICU - Configuration
 *
 * File Name: ICU.c
 *
 * Description: File include all ICU Configuration Function .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

/*                                 	ICU Header File                                                      */

#include "ICU.h"


/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL;

/*******************************************************************************
 *                    			   ICU Functions definition                                   *
 *******************************************************************************/

/*
 * Function responsible to initialize ICU pins and mode .... etc .
 */
void ICU_init(const ICU_config *ptr_config) {

	CLEAR_BIT(DDRD,PD6);	/*	Select PD6 ( ICP1 ) as input Pin */

	TCCR1A = (1 << FOC1A) | (1 << FOC1A);/* Timer1 always operates in Normal Mode */

	/*
	 * insert the required clock value in the first three bits (CS10, CS11 and CS12)
	 * of TCCR1B Register
	 */
	TCCR1B = (TCCR1B & 0xF8) | (ptr_config->prescaler);

	/* Select Edge Type Falling or Rising Type */
	TCCR1B = (TCCR1B & 0xBF) | ((ptr_config->edge_type)<<ICES1);

	TCNT1 = 0; /* initialize Timer 1 to start count from Zero */

	ICR1 = 0;	 /* initialize input capture register  to Zero */

	TIMSK |= (1 << TICIE1);	/* Enable the Input Capture interrupt  */

	return;
}

/*
 * Function responsible to Select Edge Type to make Interrupt
 */
void ICU_selectEdgeType(ICU_edgeType const ptr_config) {

	/* Select Edge Type Falling or Rising Type */
	if ((ptr_config) == RISING) {
		TCCR1B |= (1 << ICES1);	/* Select Rising Type Edge ICES1 is Edge Select bit */
	} else if ((ptr_config) == FALLING) {
		TCCR1B &= ~(1 << ICES1);	/* Select Falling Type Edge ICES1 is Edge Select bit */
	}
	return;
}

/*
 * Function responsible to Select which function call Back in Target file when interrupt execute
 */
void ICU_setCallBack(void (*a_ptr)(void)) {
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*
 * Function responsible to interrupt input capture mode
 */
ISR(TIMER1_CAPT_vect) {

	if(g_callBackPtr != NULL)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}

}

/*
 * Function responsible to read event time happen
 */
uint16 ICU_getInputCaptureValue(void) {
	/* read input capture register that event was happened */
	return ICR1;
}

/*
 * Function responsible to clear timer 1 to recount from zero
 */
void ICU_clearTimerValue(void) {
	 /* initialize Timer 1 value to start count from Zero */
	TCNT1 = 0;
}

/*
 * Function responsible to Disable Timer 1 turn off
 */
void ICU_Deinit(void) {
	/*	Clear All Timer 1 Register to Disable Timer to run */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	/* Disable Interrupt Module Flag */
	TIMSK &=~(1<<TICIE1);
}
