/*	Author: gyama009
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait, Increment, Decrement, Reset} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			PORTC = 0x07;
			state = Wait;
			break;
		case Wait:
			if(PINA & 0x01){
				state = Decrement;
			}
			else if(PINA & 0x02){
				state = Increment;
			}
			else if(PINA & 0x03){
				state = Reset;
			}
			else{
				state = Wait;
			}
			break;
		case Increment:
			state = Wait;
			break;
		case Decrement:
			state = Wait;
			break;
		case Reset:
			state = Wait;
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Wait:
			break;
		case Increment:
			PORTC += 1;
			break;
		case Decrement:
			PORTC -= 1;
			break;
		case Reset:
			PORTC = 0x00;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs
	state = Start;
	while (1) {
		Tick();	
	}
	return 0;
}
