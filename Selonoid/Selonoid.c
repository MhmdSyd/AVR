/*
 * Selonoid.c
 *
 *  Created on: Aug 7, 2020
 *      Author: Mohamed Elsayed
 */

#include "Macros.h"
#include "Micro_Config.h"
#include "Std_Types.h"

uint16 arr[4] = { 97, 194,291, 316};
uint8 indx = 0;
void servo_INIT(void);

int main(void) {
	CLEAR_BIT(DDRB, 3);
	SET_BIT(DDRA, 2);
	CLEAR_BIT(PORTA, 2);
	SET_BIT(DDRC, 0);
	CLEAR_BIT(PORTC, 0);
	SET_BIT(DDRC, 1);
	CLEAR_BIT(PORTC, 1);
	SET_BIT(DDRC, 2);
	CLEAR_BIT(PORTC, 2);
	servo_INIT();
	while (1) {
		if (BIT_IS_SET(PINB, 3)) {
			SET_BIT(PORTA, 3);
			for (indx = 0; indx < 4; indx++) {
				OCR1A = arr[indx];
				_delay_ms(2000);
			}
			CLEAR_BIT(PORTA, 2);
			SET_BIT(PORTC, 1);
			SET_BIT(PORTC, 2);
			for (indx = 0; indx < 4; indx++) {
				OCR1A = arr[indx];
				_delay_ms(2000);
			}
			CLEAR_BIT(PORTC, 1);
			CLEAR_BIT(PORTC, 2);
		}
	}
	return 0;
}

void servo_INIT(void) {
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);   //NON Inverted PWM
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1 = 4999;  //fPWM=50Hz
	DDRD |= (1 << PD4) | (1 << PD5);   //PWM Pins as Output
}
