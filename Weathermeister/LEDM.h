#include <avr/io.h>
#define F_CPU 1000000UL



void Show_T()
{
	PORTA &= ~(1 << 0); // Enable to light the LEDs
	
	PORTD|= 0b00000010;
	PORTA|= 0x00;
	PORTA|= 0x10;
	
	PORTD|= 0b00000100;
	PORTA|= 0x00;
	PORTA|= 0x10;
	
	PORTD|= 0b00001000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00010000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTA|=0b10000000; // Turn LED OFF
	
	PORTD|= 0b00100000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	
	
	
	PORTD|= 0b01000000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	
	PORTD|= 0x00;
	
}
void Show_H()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTD|= 0b00000010;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00000100;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTA|=0b10000000; //Turn LED OFF
	
	PORTD|= 0b00001000;
	PORTA|= 0x30;
	PORTA|= 0x40;
	
	PORTD|= 0b00010000;
	PORTA|= 0x30;
	PORTA|= 0x40;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b01000000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0x00;
	
}

void Show_L()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTD|= 0b00000010;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00000100;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00001000;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00010000;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b01000000;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0x00;
	
}

void Show_P()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTD|= 0b00000010;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0b00000100;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTA|=0b10000000; // Turn LED OFF
	
	PORTD|= 0b00001000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x40;
	PORTA|= 0x50;
	

	
	PORTD|= 0b00010000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x40;
	PORTA|= 0x50;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	
	PORTD|= 0b01000000;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	
	PORTD|= 0x00;
	
}

void Show_W()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTD|= 0b00000010;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000100;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00001000;
	PORTA|= 0x40;
	PORTA|= 0x50;
	
	PORTD|= 0b00010000;
	PORTA|= 0x40;
	PORTA|= 0x50;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	PORTD|= 0b01000000;
	PORTA|= 0x00;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|= 0x70;
	
	PORTD|= 0x00;
	
}

void Show_Smiley()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000010;
	PORTA|= 0x40;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000100;
	PORTA|= 0x20;
	PORTA|= 0x50;

	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00001000;
	PORTA|= 0x50;
	
	PORTD|= 0b00010000;
	PORTA|= 0x50;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x20;
	PORTA|= 0x50;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b01000000;
	PORTA|= 0x40;
	
	PORTD|= 0x00;
	
}

void Show_SadFace()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000010;
	PORTA|= 0x60;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000100;
	PORTA|= 0x20;
	PORTA|= 0x50;

	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00001000;
	PORTA|= 0x50;
	
	PORTD|= 0b00010000;
	PORTA|= 0x50;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x20;
	PORTA|= 0x50;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b01000000;
	PORTA|= 0x60;
	
	PORTD|= 0x00;
	
}

void Light_All()
{
	PORTD &= ~(1 << 7); // Enable to light the LEDs
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000010;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00000100;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;

	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b00001000;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	PORTD|= 0b00010000;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	
	PORTD|= 0b00100000;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	PORTA|=0b10000000; //Turn LED Off
	
	PORTD|= 0b01000000;
	PORTA|= 0x10;
	PORTA|= 0x20;
	PORTA|= 0x30;
	PORTA|= 0x40;
	PORTA|= 0x50;
	PORTA|= 0x60;
	
	PORTD|= 0x00;
	
}

void LedM_Init()
{
	//DDRC = 0xF0; // For the testing we don't need this
	//PORTC=0xF0;
	DDRA = 0b11111111; // Needs to be changed Column bus
	PORTA=  0x00; //Pull down
	//DDRD = ((1<<4) | (1<<5) | (1<<6) | (1<<7)); // This is ok, Demultiplexer inputs
	PORTA=0b10000000;// All LEDs are OFF
}
