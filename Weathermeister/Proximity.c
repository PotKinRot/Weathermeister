/*
 * Proximity.c
 *
 * Created: 20.06.2015 11:54:10
 *  Author: Tilmann
 */ 

#include "util/delay.h"
#include "avr/io.h"

//////////////////////////////////////////////////////////////////////////
//Actual code

void ProxySetup()
{
	DDRC |= (1 << DDRC3);	//Trigger output
	DDRD &= ~(1 << DDRD3);	//Echo input (ext. interrupt)
	
	GICR |= (1 << INT0);	//Enable external interrupt 0 for echo pin
	MCUCR |= (1 << ISC01) | (1 << ISC00);
	
	sei();	//enable global interrupts
}

//TODO: Needs to return a state => need state machine!
void ProxyDetect()
{
	if (T1 == 990)		//expects a timer that is incremented every 1ms. TODO: Will this actually work? Reliably?
	{
		PINC |= (1 << PINC3):	//activate trigger output,
		_delay_us(12);			// needs to be at least 10�s
		PINC &= ~(1 << PINC3);	//deactivate output
	}
}

ISR(INT0_vect)
{
	if (my_state == SLEEP)
	{
		_delay_us(500);
		if (PIND & (1<<PIND3))
		{
			my_state == disp_temp;
		}
}
