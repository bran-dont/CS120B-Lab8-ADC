/*	Author: Brandon Tran
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #4
 *	Exercise Description: (Challenge) Design a system, using a bank of eight LEDs, where the number of LEDs illuminated is a representation of how much light is detected. For example, when more light is detected, more LEDs are illuminated. Criteria:
The LEDs should illuminated in sequence from 0 to 7, based on the amount of light detected by the photoresistor.
Hints:
Use the MAX ADC value observed from exercise 2 as the highest amount of light detectable by the photoresistor. Divide that number by eight to determine the thresholds for each LED.

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://www.youtube.com/watch?v=x9DnUN9Hp6Q
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are in Free Running Mode,
	//			a new conversion will trigger whenever the previous conversion completes.
}

unsigned short adc;
const unsigned short MAX = 591;
unsigned char b;

void tick() {
	adc = ADC;
	
	if(adc >= (short)(MAX/8*7)) { b = 0xFF; }
	else if(adc >= (short)(MAX/8*6)) { b = 0x7F; }
	else if(adc >= (short)(MAX/8*5)) { b = 0x3F; }
	else if(adc >= (short)(MAX/8*4)) { b = 0x1F; }
	else if(adc >= (short)(MAX/8*3)) { b = 0x0F; }
	else if(adc >= (short)(MAX/8*2)) { b = 0x07; }
	else if(adc >= (short)(MAX/8*1)) { b = 0x03; }
	else { b = 0x01; }
	
	PORTB = b;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    ADC_init();
    
    while (1) {
		tick();
    }
    return 1;
}
