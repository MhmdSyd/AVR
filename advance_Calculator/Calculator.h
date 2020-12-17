/*
 * Calculator.h
 *
 *  Created on: Dec 12, 2019
 *      Author: Mohamed Elsayed
 */

#ifndef CALCULATOR_H_
#define CALCULATOR_H_

/*					Modules Header Files						*/
#include "KeyPad.h"
#include "LCD.h"



enum {
	BIG_NUMBER = 2100000, CLEAR_KEY = 8, DELAY_TIME = 300
};

/*		variable store the frist value enter by user	*/
float64 num1 = 0.0;
/*		variable store the second value enter by user	*/
float64 num2 = 0.0;
/*		variable store the result value 	*/
float64 fresult = 0.0;
/*		variable store the operation type of equation enter by user	*/
uint8 operand = 0;
/*		variable store pressed key  which we access for it	*/
uint8 key_num = 0;
/*		variable store the last pressed key before that one */
uint8 check_key = CLEAR_KEY;
/*		variable indecate that overflow is happend or not*/
uint8 overFlow=FALSE;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description: Function to store enter number by user in variables.
 */
void storNumber(float64*, uint8);

/*
 * Description: Function to clear lcd screen and variable except fresult variable.
 */
void clear(void);

/*
 * Description: main function calculate the result of equation that enter by user .
 */
void getResult(void);

/*
 * Description: Function to store operation type.
 */
void storeOperation(uint8);

/*
 * Description: Function that take number 1 & 2 & operation
 * and calculate the result and stor it in fresult variable
 */
void resultfun(void);

/*
 * Description: Function that job is print result on LCD Screen.
 */
void printResult(void);

/*
 * Description: Function take error massage and print it on LCD Screen.
 */
void error(uint8*);

/*
 * Description: Function that check if overflow has happen on result or not.
 */
void over_flow(void);

#endif /* CALCULATOR_H_ */
