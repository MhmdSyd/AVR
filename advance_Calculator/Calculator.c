/******************************************************************************
 *
 * Project : Advance Calculator - Main Code.
 *
 * File Name: Calculator.c
 *
 * Description: File include main function code  of calculator project  .
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

/*					Modules Header Files						*/

#include "Calculator.h"

/*					start of run code "main Calculator Function"						*/
int main(void) {
	LCD_init(); /*		 initialize LCD module	*/
	LCD_displayStringRowColumn(0, 3, "Calculator"); /*print "Calculator" on screen */
	_delay_ms(DELAY_TIME); /*		wait 300ms	*/
	LCD_clearScreen(); /*		clear LCD screen		*/
	LCD_goToRowColumn(0, 0); /* goto frist digit on LCD Screen */
	LCD_sendCommand(CURSOR_ON); /* show cursor to kown location of start print */

	while (1) {
		key_num = KeyPad_getPressedKey(); /*	receive press key from KeyPad 	*/
		/* check that pressed kry is number or operator */
		if (key_num >= '0' && key_num <= '9') {
			/*check if pressed key which pressed before that key is '=' to clear variable and reset calculator*/
			if (check_key == '=') {
				clear(); /*	clear variable and LCD screen */
			}
			/*check that operation variable is empty or not to choose which variable to store in */
			if (operand == 0) {
				storNumber(&num1, key_num); /*operation is empty so variable 1 will store pressed key on it*/
			} else {
				storNumber(&num2, key_num);/*operation is not empty so variable 2 will store pressed key on it*/
			}
			/*check that  pressed key is clear button so it will reset calculator again*/
		} else if (key_num == CLEAR_KEY) {
			clear(); /*clear variable and LCD screen reset calculator again */
			/*check that  pressed key is equal button so it will calculate the result and print it on LCD Screen*/
		} else if (key_num == '=') {
			/*check first before claculate that last input key entered is number 0 to 9*/
			if ((check_key >= '0') && (check_key <= '9')) {
				getResult(); /*after sure that all is ok , calculate the result and print it on LCD Screen*/
			} else {
				error("Math Error"); /*if check is not ok,so it will print error massage that something is wrong*/
			}
		} else {
			/*if there is not any key before , that mean key is operation and will go to store it*/
			storeOperation(key_num);
		}
		/*after finish check and operate the function , store that pressed key in check key variable ,
		 * because that will be old key in the next iteration*/
		check_key = key_num;
		_delay_ms(DELAY_TIME); /*wait 300ms because  MCU is faster than human*/
	}
	return 0;
}

/*
 * Description: Function that store enter number by user in variables that need pointer to float.
 */
void storNumber(float64 *num, uint8 key) {
	/*check if user enter negative number or positive*/
	if ((*num) >= 0) {
		(*num) = ((*num) * 10) + (key - 48); /*that if user enter positive number*/
	} else if ((*num) == -1) {
		(*num) = (key - 48) * -1;/*that if user enter only negative sgin*/
	} else {
		(*num) = ((*num) * 10) - (key - 48); /*that if user enter negative number*/
	}
	LCD_displayCharacter(key); /*print pressed key on Screen*/
}

/*
 * Description: Function to clear lcd screen and variable except fresult variable.
 */
void clear(void) {
	LCD_clearScreen(); /*		clear LCD screen		*/
	num1 = 0.0;
	num2 = 0.0;
	operand = 0;
	overFlow=0;

}

/*
 * Description: main function calculate the result of equation that enter by user .
 */
void getResult(void) {
	/*
	 * Description: Function that take number 1 & 2 & operation
	 * and calculate the result and stor it in fresult variable
	 */
	resultfun();
	LCD_goToRowColumn(1, 0); /*go to result print location*/
	LCD_displayCharacter('='); /*print frist '='to indcate user that is result*/
	printResult(); /*print result on LCD Screen after '=' */
}

void storeOperation(uint8 key) {
	if (check_key != CLEAR_KEY) {
		if (check_key == '=') {
			clear();
			num1 = fresult;
			LCD_floatToString(num1);
			operand = key;
			LCD_displayCharacter(key);
		} else if (check_key >= '0' && check_key <= '9') {
			if (operand == 0 && num2 == 0) {
				operand = key;
				LCD_displayCharacter(key);
			} else if (operand != 0 && num2 != 0) {
				resultfun();
				clear();
				num1 = fresult;
				LCD_floatToString(num1);
				operand = key;
				LCD_displayCharacter(key);
			} else {
				error("Math Error");
			}

		} else {
			if ((operand != 0) && (num2 == 0)) {
				fresult = num1;
				clear();
				num1 = fresult;
				LCD_floatToString(num1);
				operand = key;
				LCD_displayCharacter(key);
			} else {
				error("Math Error");
			}
		}
	} else if (key == '-') {
		LCD_displayCharacter(key);
		num1 = -1;
	} else {
		error("Math Error");
	}
}

/*
 * Description: Function that take number 1 & 2 & operation
 * and calculate the result and stor it in fresult variable
 */
void resultfun(void) {
	/*switch case that take variable and operation type and return result*/
	switch (operand) {
	case '+':
		fresult = num1 + num2;
		break;
	case '-':
		fresult = num1 - num2;
		break;
	case '*':
		fresult = num1 * num2;
		break;
	case '/':
		fresult = num1 / num2;
		break;
	default:
		fresult = num1;
		break;
	}
	return;
}

/*
 * Description: Function that job is print result on LCD Screen.
 */
void printResult(void) {
	over_flow(); /*check first there is no overflow happend or not*/
	if (overFlow == FALSE) { /*check that over flow is happend or not*/
		LCD_floatToString(fresult); /*print result because over flow was not happend*/
	} else {
		error("Big Number"); /*print massage that indacte over flow is happend*/
		overFlow = FALSE;
	}
}

/*
 * Description: Function take error massage and print it on LCD Screen.
 */
void error(uint8 *str) {
	clear(); /*clear LCD Screen to print */
	LCD_displayStringRowColumn(0, 3, str); /*print massage on LCD Screen*/
	while (KeyPad_getPressedKey() != CLEAR_KEY)
		; /*wait here untill user pressed on clear button*/
	key_num = CLEAR_KEY; /*show that clear button is the last pressed key*/
	clear(); /*clear LCD Screen and reset calculator */

}

/*
 * Description: Function that check if overflow has happen on result or not.
 */
void over_flow(void) {
	/*check that numbers are positive and operaton is add or multiply */
	if ((num1 > 0 && num2 > 0) && (operand == '+' || operand == '*')) {
		if ((sint32) fresult > 0) { /*check that result is positive also */
			overFlow = FALSE; /*over flow is not happend*/
		} else {
			overFlow = TRUE; /*over flow is happend*/
		}
	}
}
