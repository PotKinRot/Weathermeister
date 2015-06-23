/*
 * Setup.c
 */ 

#include "Proximity.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include "I2Cfncs.h"



#ifndef TIMER0_OVF_vect
#endif

void Setup()					//Main setup Function, all intialisations in here!
{
	bmp085_init();
	Initialize_LCD();
	ds1307_init();
	ProxySetup();
	Setup_Timer();
	Setup_Buttoninput();
	LedM_Init();
}


void Setup_Buttoninput()		//Defining ports for Buttons on Keypad
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

void Setup_Timer()				//Enabling Timer0 
{
	
  // Timer 0 
  TCCR0 = (1<<CS02); // Prescaler 64
  TCCR0 |= (1<<CS00);
  // Overflow Interrupt 
  TIMSK |= (1<<TOIE0);
  // Global Interrupts 
  sei();
 
}




