/******************************************************************************
 *
 * Module: MicroController 2 - Configuration
 *
 * File Name: MC2.c
 *
 * Description: File include all MicroController2 main task
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

#include "EEPROM.h"
#include "UART.h"
//`	#include "TIMER.h"

void ReciveFullPass(void);
void RecivePassword(uint32 *data);

uint8 byte;
uint16 address = 0x0311;
uint32 pass;
uint32 checker ;

int main(void){
	EEPROM_init();
	UART_init();
	DDRD |=0xE0;
	PORTD &=0x1F;

	while (1){
		byte =UART_recieveByte();
		if(byte == '*'){
			ReciveFullPass();
		}else if(byte == '+'){
			while (UART_recieveByte() != '+') {} // wait until MC1 is ready
			RecivePassword(&pass);
			if(pass == checker){
				UART_sendByte(SUCCESS);
				SET_BIT(PORTD,PD5);
				_delay_ms(10000);
				CLEAR_BIT(PORTD,PD5);
			}else{
				UART_sendByte(ERROR);
				SET_BIT(PORTD,PD7);
				_delay_ms(10000);
				CLEAR_BIT(PORTD,PD7);
			}
		}

	return 0;
}
}

void RecivePassword(uint32 *data){
	byte = UART_recieveByte();
	while (byte != '=') {
		*data = ((*data) * 10) + byte;
		PORTB ^= (1 << PB0);
		_delay_ms(500);
		byte = UART_recieveByte();

	}
}

void ReciveFullPass(void){
	while (UART_recieveByte() != '#') {} // wait until MC1 is ready
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);
	do{
		pass = 0;
		checker = 0;
		RecivePassword(&pass);
		RecivePassword(&checker);
		if (pass == checker){
			UART_sendByte(SUCCESS);
		} else{
			UART_sendByte(ERROR);
		}
	} while (pass != checker);
}

