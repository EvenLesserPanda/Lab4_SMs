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

enum States{Start, OFF_RELEASE, ON_PRESS, ON_RELEASE, OFF_PRESS} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			state = OFF_RELEASE;
			break;
		case OFF_RELEASE:
			if(PINA & 0x01){
				state = ON_PRESS;
			}
			else if(!(PINA & 0x01)){
				state = OFF_RELEASE;
			}
			break;
		case ON_PRESS:
			if(PINA & 0x01){
				state = ON_PRESS;
			}
			else if(!(PINA & 0x01)){
				state = ON_RELEASE;
			}
			break;
		case ON_RELEASE:
			if(PINA & 0x01){
				state = OFF_PRESS;
			}
			else if(!(PINA & 0x01)){
				state = ON_RELEASE;
			}
			break;
		case OFF_PRESS:
			if(PINA & 0x01){
				state = OFF_PRESS;
			}
			else if(!(PINA & 0x01)){
				state = OFF_RELEASE;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case OFF_RELEASE:
			PORTB = 0x01;
			break;
		case ON_PRESS:
			PORTB = 0x02;
			break;
		case ON_RELEASE:
			PORTB = 0x02;
			break;
		case OFF_PRESS:
			PORTB = 0x01;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	state = Start;
	while (1) {
		Tick();	
	}
	return 0;
}
