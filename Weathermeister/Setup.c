/*
 * Setup.c
 *
 * Created: 20.06.2015 16:58:09
 *  Author: Tilmann
 */ 

#include "Proximity.h"

void Setup()
{
	Setup_Schewi();
	ProxySetup();
}

void Setup_Schewi()
{
	bmp085_init();
	ds1307_init();
	Initialize_LCD();
}