/*
 * main.c
 *
 *  Created on: Sep 17, 2019
 *      Author: Mohamed Elsayed
 */
#include "Macros.h"
#include  "Micro_Config.h"
#include "Std_Types.h"


int main(void){
	DDRA = SET_BIT(DDRA,PD0);
	DDRB_REG.DATA=0xFF;

	while(1){
	PORTB_REG.BITS.BIT0=1;
	_delay_ms(500);
	PORTB=CLEAR_BIT(PORTB,PB0);
	PORTB |=(1<<PB1);
	_delay_ms(1000);
	if(BIT_IS_CLEAR(PINB,PB0)){
		PORTB_REG.BITS.BIT7=1;
		PORTB &=~(1<<PB1);
	}
	if(BIT_IS_SET(PINB,PB7)){
		PORTB_REG.BITS.BIT6 =1;
		PORTB_REG.BITS.BIT5 =1;
	}
	_delay_ms(1000);
	 ROL(PORTB,3);
	 _delay_ms(2000);
	 ROR(PORTB,3);
	 _delay_ms(1000);
	PORTB_REG.DATA =0x00;
	PORTA =TOGGLE_BIT(PORTA,PD0);
	}
	return 0;
}

