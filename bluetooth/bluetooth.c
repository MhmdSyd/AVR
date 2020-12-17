/*
 * bluetooth.c
 *
 *  Created on: May 27, 2020
 *      Author: Mohamed Elsayed
 */
#include "UART.h"

int main(void){
	SET_BIT(DDRC,0);
	SET_BIT(PORTC,0);
	UART_init();
	while(UART_recieveByte()=="#");
	while(1){
		while(UART_recieveByte()=="1");
		TOGGLE_BIT(PORTC,0);
		UART_sendByte('2');
	}
	return 0;
}
