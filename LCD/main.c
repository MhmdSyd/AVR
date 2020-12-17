

#include "LCD.h"


int main(void){
	LCD_init();
	LCD_clearScreen();
	while(1){
		LCD_displayCharacter('M');
		_delay_ms(200);
	}


	return 0;
}
