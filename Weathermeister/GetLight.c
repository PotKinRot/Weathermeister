int GetLight()
{
	int Light;
	uint16_t x;							// variable to store the ADC result
	ADCSRA = (1<<ADEN) | (1<<ADPS2);	// Enable ADC hardware i. e. ADEN=1 and
	// set ADC Pre-scaler to 16 -->
	// 1Mhz CPU clock/16 = 62.5kHz, i. e. ADPS2=1
	// (ADPS0 and ADPS1 default to 0)
	ADMUX = ADMUX | (0<<REFS1) | (1<<REFS0);   // Reference voltage = AVCC = (?V) in our case
	ADMUX = ADMUX & ~(1 << ADLAR);		// Right adjust the result registers
	// Select channel, e.g. pin 0 (which is the 1st pin at port A)
	ADMUX = ADMUX & 0b11111000;			// initialize channel bits (0-2)
	ADMUX = ADMUX | 1;					// set channel 1
	PORTA = PORTA & ~(1 << 3);			// switch off pull up resistor 3
	
	// 1st conversion:
	ADCSRA = ADCSRA | (1<<ADSC);    // start ADC
	loop_until_bit_is_clear(ADCSRA,ADSC);    // wait for completion of ADC
	// 2nd conversion:
	ADCSRA = ADCSRA | (1<<ADSC);    // start ADC
	loop_until_bit_is_clear(ADCSRA,ADSC);    // wait for completion of ADC
	x=ADCW;    // store result in 16bit-variable
					
						// Needs to be calibrated, after which the factor can be introduced here
	return x;
}
