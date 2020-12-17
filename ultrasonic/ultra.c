#include "ultra.h"

uint8 sensor_working = 0;
uint8 rising_edge = 0;
uint32 timer_counter = 0;
uint32 distance = 0;
uint8 distance_str[10];
uint8 STATE = 0;
uint16 arr[4] = { 97, 194, 291, 316 };
uint8 indx = 0;

void servo_INIT(void);

int main(void) {
	CLEAR_BIT(DDRB, 2);
	CLEAR_BIT(DDRB, 3);
	SET_BIT(DDRB, 0);
	SET_BIT(DDRC, 4);
	CLEAR_BIT(PORTC, 4);
	SET_BIT(DDRC, 0);
	CLEAR_BIT(PORTC, 0);
	SET_BIT(DDRC, 1);
	CLEAR_BIT(PORTC, 1);
	SET_BIT(DDRC, 2);
	CLEAR_BIT(PORTC, 2);

	ultrasonic_init();
	INT0_Init();
	SET_BIT(DDRA, PA1);  // Configure pin PC0 in PORTC as output pin
	CLEAR_BIT(PORTA, PA1); // Initialization Led is off at the beginning(Negative Logic)
	DDRB &= ~(1 << PB1);
	//FOR TIMER1
	servo_INIT();
	while (1) {
		if (BIT_IS_SET(PINB, 1)) {
			OCR1A = 316;  //90 degree
		} else {
			OCR1A = 97;   //0 degree
		}
		if (BIT_IS_SET(PINB, 2)) {
			ultrasonic_triger();
		} else {
			CLEAR_BIT(PORTA, 0);
		}
		if (PINB & (1 << PB0)) {
			PORTC = 0b00000110;
		} else {
			PORTC = 0x00;
		}
		if (BIT_IS_SET(PINB, 3)) {
			SET_BIT(PORTC, 4);
			for (indx = 0; indx < 4; indx++) {
				OCR1A = arr[indx];
				_delay_ms(2000);
			}
			CLEAR_BIT(PORTC, 4);
			SET_BIT(PORTC, 1);
			SET_BIT(PORTC, 2);
			for (indx = 0; indx < 4; indx++) {
				OCR1A = arr[indx];
				_delay_ms(2000);
			}
			CLEAR_BIT(PORTC, 1);
			CLEAR_BIT(PORTC, 2);
		}

	}
	return 0;
}

void timer0_init() {
	TCCR0 |= (1 << CS00); // initialising the timer with no prescaling
	TCNT0 = 0; // initialize timer
	TIMSK |= (1 << TOIE0);
}

void ultrasonic_init(void) {

	sei();
	Buzzer_DDR = 0b00000001;
	TRIGER_DDR |= (1 << TRIGER);
	ECHO_DDR &= ~(1 << ECHO);
	//ECHO_PULLUP |= (1 << ECHO);
	enable_ex_interrupt();
	timer0_init();
}

void enable_ex_interrupt(void) {

	MCUCR |= (1 << ISC10);		// Trigger INT1 on any logic change.
	GICR |= (1 << INT1);			// Enable INT1 interrupts.

	return;
}

void ultrasonic_triger(void) {
	if (!sensor_working) {
		TRIGER_PORT |= (1 << TRIGER);
		_delay_us(10);
		TRIGER_PORT &= ~(1 << TRIGER);
		sensor_working = 1;
	}
}

ISR(INT1_vect) {
	if (sensor_working == 1) {
		if (rising_edge == 0) {
			TCNT0 = 0x00;
			rising_edge = 1;
			timer_counter = 0;
		} else {
			distance = (timer_counter * 256 + TCNT0) / 446;
			// lcd_goto_xy(1,0);
			//	itoa(distance,distance_str,10);
			if (distance <= 20) {
				SET_BIT(Buzzer_port, Buzzer_pin);
			}
			if (distance > 20) {
				CLEAR_BIT(Buzzer_port, Buzzer_pin);

			}
			//strcat(distance_str, " cm ");
			//lcd_write_word(distance_str);
			_delay_ms(200);
			timer_counter = 0;
			rising_edge = 0;
		}
	}
}

ISR(TIMER0_OVF_vect) {
	timer_counter++;
	if (timer_counter > 730) {
		TCNT0 = 0x00;
		sensor_working = 0;
		rising_edge = 0;
		timer_counter = 0;
	}
}

/* External INT0 Interrupt Service Routine */
ISR(INT0_vect) {

	if (1 == STATE) {
		SET_BIT(PORTA, 1);
		SREG &= ~(1 << 7);
		MCUCR |= (1 << ISC01);
		MCUCR &= ~(1 << ISC00);
		SREG |= (1 << 7);
		STATE = 0;
	} else if (0 == STATE) {
		CLEAR_BIT(PORTA, 1);
		STATE = 1;
		SREG &= ~(1 << 7);
		MCUCR |= (1 << ISC01) | (1 << ISC00);
		SREG |= (1 << 7);
	}

}

/* External INT0 enable and configuration function */
void INT0_Init(void) {
	SREG &= ~(1 << 7);                   // Disable interrupts by clearing I-bit
	DDRD &= (~(1 << PD2));               // Configure INT0/PD2 as input pin
	GICR |= (1 << INT0);                 // Enable external interrupt pin INT0
	MCUCR |= (1 << ISC00) | (1 << ISC01);  // Trigger INT0 with the raising edge
	SREG |= (1 << 7);                    // Enable interrupts by setting I-bit
}

void servo_INIT(void) {
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);   //NON Inverted PWM
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10); //PRESCALER=64 MODE 14(FAST PWM)
	ICR1 = 4999;  //fPWM=50Hz
	DDRD |= (1 << PD5);   //PWM Pins as Output
}

void timer2_init(void) {

}

