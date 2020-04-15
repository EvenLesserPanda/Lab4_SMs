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
				state = Increment;
				PORTC += 1;
			}
			else if(PINA & 0x02){
				state = Decrement;
				PORTC -= 1;
			}
			else if(PINA & 0x03){
				state = Reset;
				PORTC = 0x00;
			}
			else{
				state = Wait;
			}
			break;
		case Increment:
			if(PINA & 0x01){
				state = Increment;
			}
			else{
				state = Wait;
			}
			break;
		case Decrement:
			if(PINA & 0x02){
				state = Decrement;
			}
			else{
				state = Wait;
			}
			break;
		case Reset:
			if(PINA & 0x03){
				state = Reset;
			}
			else{
				state = Wait;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Wait:
			break;
		case Increment:
			break;
		case Decrement:
			break;
		case Reset:
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
