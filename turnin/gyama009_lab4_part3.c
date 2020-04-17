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

enum States{Start, Lock, On_Release, Open} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			state = Lock;
			break;
		case Lock:
			if((PINA & 0x04) == 0x04){
				state = On_Release;
			}
			else{
				state = Lock;
			}
			break;
		case On_Release:
			if((PINA & 0x02) == 0x02){
				state = Open;
				PORTB = 0x01;
			}
			else if((PINA & 0x00) == 0x00){
				state = On_Release;
			}
			else{
				state = Lock;
			}
			break;
		case Open:
			if((PINA & 0x80) == 0x80){
				state = Lock;
			}
			else{
				state = Open;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case Lock:
			PINB = 0x00;
			break;
		case On_Release:
			break;
		case Open:
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
