	#include "LCD.h"

#define 	Ns			1000
#define 	Fbase		50
#define	slip			4
unsigned char arrSinU[360] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, };

unsigned char arrSinV[360] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, };

unsigned char arrSinW[360] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, };

uint8 Freq =25;
uint32 timeCycle = 0; /*time cycle (us)*/
uint32 delayTime =0;
uint32 speed = 0;

void INT1_Init(void);
void INT0_Init(void);

int main(void) {

	INT0_Init();
	INT1_Init();
	timeCycle = 1000000 /(uint32) Freq;
	delayTime = timeCycle / 360;
	speed = ((100 - slip) * ((uint32) Freq * Ns)) / (Fbase * 100);
	LCD_init();
	LCD_clearScreen();
	LCD_displayString("Freq = ");
	LCD_intgerToString(Freq);
	LCD_displayString(" HZ");
	/*
	LCD_goToRowColumn(1, 0);
	LCD_displayString("Speed = ");
	LCD_intgerToString(speed);
	LCD_displayString(" RPM");*/

	SET_BIT(DDRC, 0);
	CLEAR_BIT(PORTC, 0);
	SET_BIT(DDRC, 1);
	CLEAR_BIT(PORTC, 1);
	SET_BIT(DDRC, 2);
	CLEAR_BIT(PORTC, 2);
	SET_BIT(DDRC, 3);
	CLEAR_BIT(PORTC, 3);
	SET_BIT(DDRC, 4);
	CLEAR_BIT(PORTC, 4);
	SET_BIT(DDRC, 5);
	CLEAR_BIT(PORTC, 5);
	while (1) {
		for (int i = 0; i < 360; i++) {
			if (arrSinU[i] == 0) {
				CLEAR_BIT(PORTC, 0);
				SET_BIT(PORTC, 1);
			} else {
				CLEAR_BIT(PORTC, 1);
				SET_BIT(PORTC, 0);
			}
			if (arrSinV[i] == 0) {
				CLEAR_BIT(PORTC, 2);
				SET_BIT(PORTC, 3);
			} else {
				CLEAR_BIT(PORTC, 3);
				SET_BIT(PORTC, 2);
			}
			if (arrSinW[i] == 0) {
				CLEAR_BIT(PORTC, 4);
				SET_BIT(PORTC, 5);
			} else {
				CLEAR_BIT(PORTC, 5);
				SET_BIT(PORTC, 4);
			}
			_delay_us(delayTime);
		}
	}
	return 0;
}

/* External INT0 enable and configuration function */
void INT0_Init(void) {
	SREG &= ~(1 << 7);                   // Disable interrupts by clearing I-bit
	DDRD &= (~(1 << PD2));               // Configure INT0/PD2 as input pin
	GICR |= (1 << INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1 << ISC00) | (1 << ISC01);  // Trigger INT0 with the raising edge
	SREG |= (1 << 7);                    // Enable interrupts by setting I-bit
}

/* External INT1 enable and configuration function */
void INT1_Init(void) {
	SREG &= ~(1 << 7);      // Disable interrupts by clearing I-bit
	DDRD &= (~(1 << PD3));  // Configure INT1/PD3 as input pin
	GICR |= (1 << INT1);    // Enable external interrupt pin INT1
	MCUCR |= (1 << ISC11) | (1 << ISC10);	// Trigger INT1 with the Rise edge
	SREG |= (1 << 7);       // Enable interrupts by setting I-bit
}

/* External INT0 Interrupt Service Routine */
ISR(INT0_vect) {
	Freq -= 5;
	if(Freq <= 5) Freq= 5;
	timeCycle = 1000000 /(uint32) Freq;
	delayTime = timeCycle / 360;
	speed = ((100 - slip) * ((uint32) Freq * Ns)) / (Fbase * 100);
	LCD_clearScreen();
	LCD_displayString("Freq = ");
	LCD_intgerToString(Freq);
	LCD_displayString(" HZ");
	/*
	LCD_goToRowColumn(1, 0);
	LCD_displayString("Speed = ");
	LCD_intgerToString(speed);
	LCD_displayString(" RPM");*/
}

/* External INT1 Interrupt Service Routine */
ISR(INT1_vect) {
	Freq += 5;
	if(Freq >= Fbase) Freq= Fbase;
	timeCycle = 1000000 / (uint32)Freq;
	delayTime = timeCycle / 360;
	speed = ((100 - slip) * ((uint32) Freq * Ns)) / (Fbase * 100);
	LCD_clearScreen();
	LCD_displayString("Freq = ");
	LCD_intgerToString(Freq);
	LCD_displayString(" HZ");
	LCD_goToRowColumn(1, 0);
	/*
	LCD_displayString("Speed = ");
	LCD_intgerToString(speed);
	LCD_displayString(" RPM");*/
}

