/*
 * main.c
 *
 *  Created on: Sep 25, 2019
 *      Author: Mohamed Elsayed
 */

#include "SPI.h"
#include "LCD.h"

uint8 key =0;

int main(void)
{
	uint8 key;
	LCD_init();
	SPI_initSlave(); //initialize salve MC
    while(1)
    {
		key = SPI_receiveByte();  //receive the pressed key from spi
		if((key>=48) && (key<=57))
		{
			LCD_intgerToString(key - 48); //display the pressed key
		}
		else
		{
			LCD_displayCharacter(key);
		}
    }
}

