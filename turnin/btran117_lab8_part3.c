/*	Author: Brandon Tran
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #3
 *	Exercise Description: Design a system where an LED is illuminated only if enough light is detected from the photo resistor. Criteria:
If the result of the ADC is >= MAX/2, the LED is illuminated.
If the result of the ADC is < MAX/2, the LED is turned off.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo Link: https://www.youtube.com/watch?v=GXuTddWxvI4
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
const unsigned char MAX = 591;

void tick() {
	adc = ADC;
	
	PORTB = (adc >= MAX/2 ? 1 : 0);
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
