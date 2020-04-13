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
#include "RIMS.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, s0, s1} state;

void Tick(){
	switch(state){
		case Start: // Initial transition
			state = s0;
			break;
		case s0:
			if(A0){
				state = s1;
			}
			else if(!A0){
				state = s0;
			}
			break;
		case s1:
			if(A0){
				state = s0;
			}
			else if(!A0){
				state = s1;
			}
			break;
		default:
			state = Start;
			break;
	} // Transitions
	switch(state){ // State actions
		case s0:
			B0 = 1;
			B1 = 0;
			break;
		case s1:
			B0 = 0;
			B1 = 1;
			break;
		default:
			break;
	} // State actions
}

int main(void) {
	//DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	//DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	B = 0x00;
	state = Start;
	while (1) {
		Tick();	
	}
	return 0;
}
