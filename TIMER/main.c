/*
 * main.c
 *
 *  Created on: Oct 2, 2019
 *      Author: Mohamed Elsayed
 */
#include "TIMER.h"

#define N					1024
#define TIME_SEC		(((F_CPU)/(N))-1)

TIMER_Config setTimer={CTC,F_CPU_1024,TIME_SEC * 60};



void TogglePin(void){
	if(setTimer.mode == OVF){
		PORTC ^=(1<<PC0);
	}
	if(setTimer.mode == CTC){
		PORTC ^=(1<<PC1);
	}

}

int main(void){
	DDRC=0xFF;
	PORTC=0x00;
	TIMER_init(&setTimer);
	TIMER_setCallBack(TogglePin);
	_delay_ms(5000);

	while(1){

	}
	return 0;
}
