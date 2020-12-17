/*
 * ultra.h
 *
 *  Created on:
 *      Author: 3step
 */

#ifndef ULTRA_H_
#define ULTRA_H_

#define F_CPU 8000000UL
#include "Macros.h"
#include "Std_Types.h"
#include "Micro_Config.h"

#define   TRIGER_DDR    DDRD
#define   ECHO_DDR      DDRD
#define   TRIGER_PORT   PORTD
#define   ECHO_PULLUP   PORTD
#define   TRIGER        0
#define   ECHO          3
#define   	Buzzer_DDR	DDRA
#define	Buzzer_port	PORTA
#define	Buzzer_pin	PIN0
#define   Led_DDR	DDRA
#define	Led_port	PORTA
#define	Led_pin	PIN1

/*************************************************
 *  API functions
 *************************************************/
void timer0_init();
void ultrasonic_init(void);
void enable_ex_interrupt(void);
void ultrasonic_triger(void);


#endif /* ULTRA_H_ */
