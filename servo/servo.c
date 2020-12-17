#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "Macros.h"

void servo_INIT(void);
void main()
{
	DDRB &=~(1<<PB1);
  //FOR TIMER1
 servo_INIT();
   while(1)
   {
	   if(BIT_IS_SET(PINB,1) ){
      OCR1A=316;  //180 degree
	   }else{
      OCR1A=97;   //0 degree
	   }
   }
}
 void servo_INIT(void){
	  TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	   TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //PRESCALER=64 MODE 14(FAST PWM)
	   ICR1=4999;  //fPWM=50Hz
	   DDRD|=(1<<PD4)|(1<<PD5);   //PWM Pins as Output
 }
