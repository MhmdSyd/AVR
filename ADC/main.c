/*
 * main.c
 *
 *  Created on: Sep 18, 2019
 *      Author: Mohamed Elsayed
 */

#include "ADC.h"
#include "LCD.h"

extern volatile sint16 g_adcResult;
sint16 volatile result;
ADC_Config pin1={internal_Vref,OFF,F_CPU_8} ;
int main(void)
{
	uint8 customChar[8] = { 0x18, 0x18, 0x03, 0x04, 0x04, 0x04, 0x03, 0x00 };
	LCD_init(); /* initialize LCD driver */
	ADC_init(&pin1); /* initialize ADC driver */
	LCD_creatCustomChar(1, customChar);
	LCD_clearScreen(); /* clear LCD at the beginning */
	/* display this string "ADC Value = " only once at LCD */
	LCD_displayString("ADC Value = ");

    while(1)
    {

		LCD_goToRowColumn(0,12); /* display the number every time at this position */
		 ADC_readChannel(0, CLOSE); /* read channel zero where the potentiometer is connect */
		 result =(g_adcResult * 4.88)/10;
		LCD_intgerToString(result); /* display the ADC value on LCD screen */
		LCD_displayCharacter(1);
		LCD_displayString("   ");
		_delay_ms(100);
    }
}

