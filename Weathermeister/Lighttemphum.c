#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "I2Cfncs.h"
#include "Lighttemphum.h"
#include <math.h>

#define EULERNUMBER 2.718281828459 //For the Light Curve

float Get_Hum(void)
{
	char printbuff[100];
	int8_t temperature = 0;
	float humidity;
	dht_gettemperaturehumidity(&temperature, &humidity);
	dtostrf(temperature, 3, 3, printbuff);
	dtostrf(humidity, 3, 3, printbuff);

			 
	
	
	return humidity;
}



#if DHT_FLOAT == 1
int8_t dht_getdata(float *temperature, float *humidity) {
#elif DHT_FLOAT == 0
int8_t dht_getdata(int8_t *temperature, int8_t *humidity) {
#endif
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	DHT_DDR |= (1<<DHT_INPUTPIN); //output
	DHT_PORT |= (1<<DHT_INPUTPIN); //high
	_delay_ms(100*8);

	//send request
	DHT_PORT &= ~(1<<DHT_INPUTPIN); //low
	_delay_us(500*8);
	
	DHT_PORT |= (1<<DHT_INPUTPIN); //high
	DHT_DDR &= ~(1<<DHT_INPUTPIN); //input
	_delay_us(40*8);

	//check start condition 1
	if((DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80*8);
	//check start condition 2
	if(!(DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80*8);

	//read the data
	uint16_t timeoutcounter = 0;
	for (j=0; j<5; j++) { //read 5 byte
		uint8_t result=0;
		for(i=0; i<8; i++) {//read every bit
			timeoutcounter = 0;
			while(!(DHT_PIN & (1<<DHT_INPUTPIN))) { //wait for an high input (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1; //timeout
				}
			}
			_delay_us(30*8);
			if(DHT_PIN & (1<<DHT_INPUTPIN)) //if input is high after 30 us, get result
				result |= (1<<(7-i));
			timeoutcounter = 0;
			while(DHT_PIN & (1<<DHT_INPUTPIN)) { //wait until input get low (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1; //timeout
				}
			}
		}
		bits[j] = result;
	}

	//reset port
	DHT_DDR |= (1<<DHT_INPUTPIN); //output
	DHT_PORT |= (1<<DHT_INPUTPIN); //low
	_delay_ms(100*8);

	//check checksum
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
		//return temperature and humidity
		uint16_t rawhumidity = bits[0]<<8 | bits[1];
		uint16_t rawtemperature = bits[2]<<8 | bits[3];
		if(rawtemperature & 0x8000) {
			*temperature = (float)((rawtemperature & 0x7FFF) / 10.0) * -1.0;
		} else {
			*temperature = (float)(rawtemperature)/10.0;
		}
		*humidity = (float)(rawhumidity)/10.0;
		return 0;
	}

	return -1;
}

/*
 * get temperature
 */
#if DHT_FLOAT == 1
int8_t dht_gettemperature(float *temperature) {
	float humidity = 0;
#elif DHT_FLOAT == 0
int8_t dht_gettemperature(int8_t *temperature) {
	int8_t humidity = 0;
#endif
	return dht_getdata(temperature, &humidity);
}

/*
 * get humidity
 */
#if DHT_FLOAT == 1
int8_t dht_gethumidity(float *humidity) {
	float temperature = 0;
#elif DHT_FLOAT == 0
int8_t dht_gethumidity(int8_t *humidity) {
	int8_t temperature = 0;
#endif
	return dht_getdata(&temperature, humidity);
}

/*
 * get temperature and humidity
 */
#if DHT_FLOAT == 1

int8_t dht_gettemperaturehumidity(float *temperature, float *humidity) {
#elif DHT_FLOAT == 0
	int8_t dht_gettemperaturehumidity(int8_t *temperature, int8_t *humidity) 
	{
#endif
	return dht_getdata(temperature, humidity);
}




int Get_Light()
{
	long Light;
	uint16_t x;							// variable to store the ADC result
	float reading;
	float freading;
	float fresult;
	ADCSRA = (1<<ADEN) | (1<<ADPS2);	// Enable ADC hardware i. e. ADEN=1 and
	// set ADC Pre-scaler to 16 -->
	// 1Mhz CPU clock/16 = 62.5kHz, i. e. ADPS2=1
	// (ADPS0 and ADPS1 default to 0)
	ADMUX = ADMUX | (0<<REFS1) | (1<<REFS0);   // Reference voltage = AVCC = (?V) in our case
	ADMUX = ADMUX & ~(1 << ADLAR);		// Right adjust the result registers
	// Select channel, e.g. pin 0 (which is the 1st pin at port A)
	ADMUX = ADMUX & 0b11111110;			// initialize channel bits (0)
	ADMUX = ADMUX | 0;					// set channel 0
	PORTA = PORTA | 0b00000001;			// switch off pull up resistor 0
	
	// 1st conversion:
	ADCSRA = ADCSRA | (1<<ADSC);    // start ADC
	loop_until_bit_is_clear(ADCSRA,ADSC);    // wait for completion of ADC
	// 2nd conversion:
	ADCSRA = ADCSRA | (1<<ADSC);    // start ADC
	loop_until_bit_is_clear(ADCSRA,ADSC);    // wait for completion of ADC
	reading=ADCW;    // store result in 16bit-variable
	//x=(x*0.0048828125)	
	reading = 1023-reading;
	freading = reading;	
	
	if(reading>=0 && reading<=155) {  // Darkness
		fresult = 0.0;
	}
	if(reading>155 && reading<=350) {
		// y = 0,0042273988x2 - 1,0130028488x + 55,4403759239
		fresult = 0.0042273988 * freading * freading - 1.0130028488 * freading + 55.4403759239;
	}
	if(reading>350 && reading<=650) {
		// y = 11,7717399221e0,0083003710x
		fresult = 11.7717399221 * pow(EULERNUMBER, (0.0083003710 * freading));
	}
	if(reading>650 && reading<=936) {
		// y = 0,3373539789e0,0134529914x
		fresult = 0.3373539789 * pow(EULERNUMBER, (0.0134529914 * freading)) + 448.5;
	}
	if(reading>980) {                 // Upper limit of measurement
		fresult = 100000.6;
	}	
		// Needs to be calibrated, after which the factor can be introduced here
	return fresult;
}


