/*
 * LEDM.c
 *
 * Created: 24.06.2015 20:20:28
 *  Author: Schewi
 */ 

#include "avr/io.h"

void Row(int n)
{
	switch (n)
	{
		case 1:
		{
			PORTD &= ~((1<<4) | (1<<5) | (1<<6));
			break;
		}
		
		case 2:
		{
			PORTD &= ~((1<<5) | (1<<6)); PORTD |= (1<<4);
			break;
		}
		
		case 3:
		{
			PORTD &= ~((1<<4) | (1<<6)); PORTD |= (1<<5);
			break;
		}
		
		case 4:
		{
			PORTD |= ((1<<4) | (1<<5)); PORTD &= ~(1<<6);
			break;
		}
		
		case 5:
		{
			PORTD &= ~((1<<4) | (1<<5)); PORTD |= (1<<6);
			break;
		}
		
		case 6:
		{
			PORTD |= ((1<<4) | (1<<6)); PORTD &= ~(1<<5);
			break;
		}
		
		case 7:
		{
			PORTD |= ((1<<5) | (1<<6)); PORTD &= ~(1<<4);
			break;
		}
		
		case 8:
		{
			PORTD |= ((1<<4) | (1<<5) | (1<<6));
			break;
		}
		
	}

}

void Column(int m)
{
	switch(m)
	{
		case 1:
		{
			PORTA &= ~((1<<2) | (1<<3) | (1<<4)| (1<<5) | (1<<6));
			PORTA|= (1<<1);
			break;
		}
		
		case 2:
		{
			PORTA|= (1<<2);
			PORTA &= ~((1<<1) | (1<<3) | (1<<4)| (1<<5) | (1<<6));
			break;
		}
		
		case 3:
		{
			PORTA|= (1<<3);
			PORTA &= ~((1<<2) | (1<<1) | (1<<4)| (1<<5) | (1<<6));
			break;
		}
		
		case 4:
		{
			PORTA|= (1<<4);
			PORTA &= ~((1<<2) | (1<<3) | (1<<1)| (1<<5) | (1<<6));
			break;
		}
		
		case 5:
		{
			PORTA|= (1<<5);
			PORTA &= ~((1<<2) | (1<<3) | (1<<4)| (1<<1) | (1<<6));
			break;
		}
		
		case 6:
		{
			PORTA|= (1<<6);
			PORTA &= ~((1<<2) | (1<<3) | (1<<4)| (1<<5) | (1<<1));
			break;
		}
	}
	
}

void Show_T()
{
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(1);//Row1
	Row(2);//Row2
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(1);//Row1
	Row(2);//Row2
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(1);//Row1
	Row(2);//Row2
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(1);//Row1
	Row(2);//Row2
	
}
void Show_H()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(4);//Row4
	Row(5);//Row5
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(4);//Row4
	Row(5);//Row5
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
}
void Show_L()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(7);//Row7
	Row(8);//Row8
	
	
}
void Show_P()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(1);//Row1
	Row(2);//Row2
	Row(5);//Row5
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(1);//Row1
	Row(2);//Row2
	Row(5);//Row5
	Row(6);//Row6
	
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4

}
void Show_W()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(6);//Row6
	Row(7);//Row7
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(5);//Row5
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(5);//Row5
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(6);//Row6
	Row(7);//Row7
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(1);//Row1
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	Row(8);//Row8
	
}
void Show_Smiley()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(5);//Row5
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(3);//Row3
	Row(6);//Row6

	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(3);//Row3
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(5);//Row5
	
}
void Show_SadFace()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(7);//Row7
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(3);//Row3
	Row(6);//Row6

	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(3);//Row3
	Row(6);//Row6
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(7);//Row7
}
void Light_All()
{
	PORTD &= ~(1 << 7);// Enable LED
	Column(1);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(2);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(3);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(4);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(5);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	
	PORTD &= ~(1 << 7);// Enable LED
	Column(6);
	Row(2);//Row2
	Row(3);//Row3
	Row(4);//Row4
	Row(5);//Row5
	Row(6);//Row6
	Row(7);//Row7
	
	
	
}
void LedM_Init()
{
	DDRA |= ((1<<1) | (1<<2) | (1<<3) | (1<<4)| (1<<5) | (1<<6)); // Needs to be changed Column bus
	PORTA &= ~((1<<1) | (1<<2) | (1<<3) | (1<<4)| (1<<5) | (1<<6));//Pull down
	DDRD |= ((1<<4) | (1<<5) | (1<<6) | (1<<7)); // This is ok, Demultiplexer inputs
	PORTD|= (1<<7);// All LEDs are OFF
}
