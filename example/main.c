#include "KeyPad.h"
#include  "LCD.h"
#include <math.h>

void operator(void);
void resultfun(void);


sint8 *String = "Calculator";
uint8 key_num = 0;
sint32 num1 = 0;
sint32 num2 = 0;
uint8 operand = 0;
sint32 result = 0;
int main(void) {
	LCD_init();
	LCD_sendCommand(CURSOR_HOME_LOCATION);
	LCD_goToRowColumn(0, 3);
	LCD_displayString(String);
	_delay_ms(1000);
	LCD_sendCommand(CURSOR_ON);
	while (1) {
		LCD_clearScreen();
		LCD_goToRowColumn(0, 0);
		_delay_ms(500);
		LCD_clearScreen();
		LCD_sendCommand(CURSOR_HOME_LOCATION);
		do {
				key_num = KeyPad_getPressedKey();
				if ((key_num <= 57) && (key_num >= 48)) {
					LCD_displayCharacter(key_num);
					num1 = (sint32) (key_num - 48) + (num1 * 10);
				}
				_delay_ms(500);

		} while ((key_num <= 57) && (key_num >= 48));
		operator();
		LCD_displayCharacter(key_num);
	_delay_ms(500);

	do {
			key_num = KeyPad_getPressedKey();
			if ((key_num <= 57) && (key_num >= 48)) {
				LCD_displayCharacter(key_num);
				num2 = (sint32) (key_num - 48) + (num2 * 10);
			}
			_delay_ms(500);

	} while ((key_num <= 57) && (key_num >= 48));
		LCD_displayCharacter(key_num);
		resultfun();
		LCD_intgerToString(result);
		while (key_num != 27) {
			key_num = KeyPad_getPressedKey();
		}
		key_num = 0;
		num1 = 0;
		num2 = 0;
		operand = 0;
		result = 0;

	}

	return 0;
}

void operator(void) {
	operand = key_num;

	return;
}

void resultfun(void) {

	switch (operand) {
	case 43:
		result = num1 + num2;
		break;
	case 45:
		result = num1 - num2;
		break;
	case 42:
		result = num1 * num2;
		break;
	case 47:
		result = num1 / num2;
		break;
	default:
		result = 0;
		break;
	}

	return;
}

