/*
 * Setup.c
 *
 * Created: 20.06.2015 16:58:09
 *  Author: Tilmann
 */ 

#include "Proximity.h"
#include <avr/interrupt.h>
#include <avr/io.h>


#ifndef TIMER0_OVF_vect
#endif

void Setup()
{
	Setup_Schewi();
	ProxySetup();
	Setup_Timer();
	Setup_Buttoninput();
}

void Setup_Schewi()
{
	bmp085_init();
	ds1307_init();
	Initialize_LCD();
}

void Setup_Buttoninput()
{
	DDRC  &= ~(1<<PC7);
	PORTC |= (1<<PC7);
	DDRC  &= ~(1<<PC6);
	PORTC |= (1<<PC6);
	DDRC  &= ~(1<<PC5);
	PORTC |= (1<<PC5);
	DDRC  &= ~(1<<PC4);
	PORTC |= (1<<PC4);
	
}


void Setup_Timer()
{
	
  // Timer 0 konfigurieren
  TCCR0 = (1<<CS02); // Prescaler 64
  TCCR0 |= (1<<CS00);
  // Overflow Interrupt erlauben
  TIMSK |= (1<<TOIE0);
  // Global Interrupts aktivieren
  sei();
 
}




