/*
 * main.c
 *
 *  Created on: Sep 18, 2019
 *      Author: Mohamed Elsayed
 */

/* Only check LCD code to sure that code write correctly */
#include "LCD.h"
#include "ICU.h"
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPlusHigh = 0;

void APP_edgeProcessing(void) {
	g_edgeCount++;
	if (g_edgeCount == 1) {
		/*
		 * Clear the timer counter register to start measurements from the
		 * first detected rising edge
		 */
		ICU_clearTimerValue();
		/* Detect falling edge */
		ICU_selectEdgeType(FALLING);
	} else if (g_edgeCount == 2) {
		/* Store the High time value */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Detect rising edge */
		ICU_selectEdgeType(RISING);
	} else if (g_edgeCount == 3) {
		/* Store the Period time value */
		g_timePeriod = ICU_getInputCaptureValue();
		/* Detect falling edge */
		ICU_selectEdgeType(FALLING);
	} else if (g_edgeCount == 4) {
		/* Store the Period time value + High time value */
		g_timePeriodPlusHigh = ICU_getInputCaptureValue();
		/* Clear the timer counter register to start measurements again */
		ICU_clearTimerValue();
		/* Detect rising edge */
		ICU_selectEdgeType(RISING);
	}
}

int main() {
	uint32 dutyCycle = 0;

	/* Create configuration structure for ICU driver */
	ICU_config Icu_Config = { F_CPU_CLOCK, RISING };

	/* Enable Global Interrupt I-Bit */
	SREG |= (1 << 7);

	/* Set the Call back function pointer in the ICU driver */
	ICU_setCallBack(APP_edgeProcessing);

	/* Initialize both the LCD and ICU driver */
	LCD_init();
	ICU_init(&Icu_Config);

	while (1) {
		if (g_edgeCount == 4) {
			ICU_Deinit(); /* Disable ICU Driver */
			g_edgeCount = 0;
			LCD_displayString("Period = ");
			/* calculate the dutyCycle */
			dutyCycle = (float) ((g_timePeriodPlusHigh - g_timeHigh) /(g_timePeriodPlusHigh - g_timeHigh)) * 100;
			/* display the dutyCycle on LCD screen */
			LCD_intgerToString(dutyCycle);
			LCD_displayString(" %");

		}
	}
}
