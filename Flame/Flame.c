/*
 * Flame.c
 *
 *  Created on: Aug 6, 2020
 *      Author: Mohamed Elsayed
 */

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB&=~(1<<0);
    DDRC|=(1<<0);
    DDRC|=(1<<1);
    DDRC|=(1<<2);
    PORTC&=(1<<0);
    PORTC&=(1<<1);
    PORTC&=(1<<2);


    while(1)
    {
     if(PINB & (1<<PB0))
		{
			PORTC &= (~(1<<PC0));
			PORTC |= (1<<PC1);
			PORTC |= (1<<PC2);
		}
		else
            {
			PORTC &= (~(1<<PC0));
			PORTC &= (~(1<<PC1));
			PORTC &= (~(1<<PC2));
		    }
}
}

