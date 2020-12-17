/*
 * MC2.c
 *
 * Created: 4/10/2014 11:23:48 PM
 * Author: mohamed tarek
 */

#include "UART.h"
#include "LCD.h"

#define M2_READY 0x10
uint8 key=0;
int main(void)
{
	uint8 Str[20];
	UART_init(); // initialize UART driver
	LCD_init(); // initialize LCD driver
	UART_sendByte('#'); // MC2 is ready
	UART_receiveString(Str); // receive the string
	LCD_displayString(Str); // display the string on LCD
    while(1)
    {
    	key = UART_recieveByte();
    	if(key >= 48 && key <= 57){
    		key -=48;
    	LCD_goToRowColumn(1, 3);
    	LCD_intgerToString(key);
    	LCD_displayCharacter(' ');
    	}
    }
}
