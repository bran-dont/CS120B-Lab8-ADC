/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #8  Exercise #1
 *	Exercise Description: Make sure your breadboard is wired according to the prelab. The potentiometer is used to adjust the voltage supplied to the microcontroller for ADC . Design a system that reads the 10-bit ADC result from the ADC register, and displays the result on a bank of 10 LEDs.
Hints:
Assuming the breadboard has been wired according to the prelab photo, display the lower 8 bits on port B, and the upper 2 bits on port D.
Use a “short” variable to hold the ADC result.
Use bit shifting and casting to align the proper bits to the proper ports. For example:

 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
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
unsigned char b, d;

void tick() {
	adc = ADC;
	b = adc;
	d = (adc >> 8);
	
	PORTB = b;
	PORTD = d;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    ADC_init();
    
    while (1) {
		tick();
    }
    return 1;
}
