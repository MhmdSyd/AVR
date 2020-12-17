/*
 * External_EEPROM_I2C.c
 *
 * Created: 3/12/2014 12:05:19 PM
 *  Author: Mohamed Tarek
 */
#include "Macros.h"
#include "EEPROM.h"
#include "LCD.h"

int main(void)
{
	LCD_init();
	uint8 i;
	uint8 byte =0;
	uint32 pass=0;
	uint32 passCheck=0;
	DDRB  = 0xFF;
	PORTB = 0x00;

	/* Init EEPROM */
	EEPROM_init();
	for(i=0;i<4;i++){
		EEPROM_readByte((0x0311 + i), &byte);
		_delay_ms(10);
		passCheck=(passCheck) | ((uint32)byte<<(8*i));
	}
	LCD_displayString("  PASSWORD ");
	LCD_goToRowColumn(1, 0);
	LCD_intgerToString(passCheck);
	_delay_ms(2000);
	pass = 12345;
	for(i=0;i<4;i++){
		EEPROM_writeByte((0x0311 + i),(pass>>(8*i)));
		_delay_ms(10);
	}

	for(i=0;i<4;i++){
		EEPROM_readByte((0x0311 + i), &byte);
		_delay_ms(10);
		passCheck=(passCheck) | ((uint32)byte<<(8*i));
	}
	LCD_clearScreen();
	LCD_displayString("  PASSWORD ");
	LCD_goToRowColumn(1, 0);
	LCD_intgerToString(passCheck);
while(1)
	{
		if(passCheck ==pass){
			PORTB= 0xFF;
		}else{
			PORTB = 0x0F;
		}

	}
	return 0;
}
