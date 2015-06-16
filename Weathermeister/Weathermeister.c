/*
 * Weathermeister.c
 *
 * Created: 09.06.2015 14:37:49
 *  Author: Tilmann
 */ 


#include <avr/io.h>
#include <LCD.h>
#include <I2C_master.h>
#include <i2cfncs.h>
#include <DS1307new.h>



int main(void)
{
	
	Initialize_LCD();
	
    while(1)
    {
		Send_Character("Test");
		
        //TODO:: Please write your application code 
    }
}