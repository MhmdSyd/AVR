 /******************************************************************************
 *
 * Module: Traffic
 *
 * File Name: Traffic.c
 *
 * Description: File include main function of Traffic target
 *
 * Author: Mohamed Elsayed
 *
 *******************************************************************************/

#include "TIMER.h"

#define N					1024
#define TIME_SEC		(((F_CPU)/(N))-1)

void trafficToggelLed(void);

 typedef enum{
	RED,RED_YELLOW,GREEN,GREEN_YELLOW
}Mode;

Mode mode;

TIMER_Config *setTimer={CTC,F_CPU_1024,TIME_SEC * 10};

uint8 index=0;

uint8 pinOut[4]={0x21,0x33,0x0C,0x1E};



uint8 main(void){
	DDRC |=0x3F;
	PORTC=0x21;
	TIMER_init(&setTimer);
	TIMER_setCallBack(trafficToggelLed);

	while(1){

	}
	return 0;
}

void trafficToggelLed(void){
	index =(++index)%6;
	if((index == 5)&&(mode == RED)){
		mode = RED_YELLOW;
	}else if((index == 5)&&(mode == GREEN)){
		mode = GREEN_YELLOW;
	}else if((index == 1)&&(mode == RED_YELLOW)){
		mode = GREEN;
	}else if((index == 1)&&(mode == GREEN_YELLOW)){
		mode = RED;
	}
	PORTC=pinOut[mode];
}



