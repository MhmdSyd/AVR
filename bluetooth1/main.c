/*main file*/
#include <avr/interrupt.h>
#include "KeyPad.h"
#include "UART.h"
#include "LCD.h"

uint8 index = 0;
bool state = 0;
uint8 passWord[10] = "1234";
uint8 flag = 0;
uint8 arrPass[10];
void INT0_Enable(void);
uint8 compare(uint8*, uint8*);
void LED_init(void);
void arr_init(uint8*, uint8);
void IR_init(void);
void SLEEP_Mode(void);
int main(void) {
	INT0_Enable();
	LCD_init();
	UART_init();
	LED_init();
	LCD_displayStringRowColumn(0, 3, "Enter Pass");
	IR_init();

	while (1) {
		if (BIT_IS_SET(PINB, 7)) {
			//while(UART_recieveByte() != '#' );
			arr_init(arrPass, 10);
			LCD_goToRowColumn(1, 0);
			if (state == FALSE) {
				index = 0;

				do {
					flag = KeyPad_getPressedKey();
					arrPass[index] = flag;
					index++;
					LCD_displayCharacter('*');
					_delay_ms(100);

				} while (flag != '#');
				arrPass[index] = '\0';
			} else {
				while (UART_recieveByte() != '#');
				UART_receiveString(arrPass);
				SET_BIT(PORTB, 1);
			}
			flag = compare(arrPass, passWord);
			LCD_clearScreen();
			if (flag == 0) {
				SET_BIT(PORTB, 0);
				LCD_displayStringRowColumn(0, 3, "Correct Pass");
				UART_sendByte('o');
			} else {
				CLEAR_BIT(PORTB, 0);
				LCD_displayStringRowColumn(0, 3, "Error Pass");
				UART_sendByte('N');
			}
			_delay_ms(500);
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 3, "Enter Pass");
		}else{
			SLEEP_Mode();
		}
	}
	return 0;
}

void INT0_Enable(void) {
	SET_BIT(SREG, 7);
	SET_BIT(GICR, 6);
	SET_BIT(MCUCR, 0);
	SET_BIT(MCUCR, 1);
}

uint8 compare(uint8 *arr1, uint8 *arr2) {
	int index = 0, check = 0;
	while (arr2[index] != '\0' && check == 0) {
		if (arr1[index] == arr2[index]) {
			index++;
		} else {
			check++;
		}

	}
	return check;
}

ISR(INT0_vect) {
	state = !(state);
	TOGGLE_BIT(PORTB, 1);
	LCD_goToRowColumn(1, 0);
	LCD_displayCharacter(state + '0');
}

void LED_init(void) {
	SET_BIT(DDRB, 0);
	SET_BIT(DDRB, 1);
	CLEAR_BIT(PORTB, 0);
	CLEAR_BIT(PORTB, 1);
}

void arr_init(uint8 *arr, uint8 x) {
	for (uint8 i = 0; i < x; i++) {
		arr[i] = 0;
	}

}

void IR_init(void) {
	CLEAR_BIT(DDRB, 7);
}

void SLEEP_Mode(void){
	LCD_clearScreen();
}
