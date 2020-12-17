/*
 * MC1.c
 *
 * Created: 4/10/2014 11:21:37 PM
 * Author: mohamed tarek
 */

#include "UART.h"
#include "KeyPad.h"


uint8 key=0;

int main(void)
{
	UART_init(); // initialize UART
	while(UART_recieveByte() != '#'){} // wait until MC2 is ready
	DDRA=0x00;
	PORTA=0xFF;
	UART_sendString("I am Micro1"); // send the required string to MC2

    while(1)
    {
    	key = KeyPad_getPressedKey();
    	UART_sendByte(key);
    	_delay_ms(500);
    }
}
