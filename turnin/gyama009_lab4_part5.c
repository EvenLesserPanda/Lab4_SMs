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

unsigned char unlock;
int arr[4];
int hold;

void Tick(){
	switch(state){
		case Start: // Initial transition
			state = Lock;
			unlock = 0;
			hold = 0;
			break;
		case Lock:
			if((PINA & 0x04) == 0x04){
				state = On_Release;
				hold = 0;
				arr[hold] = 4;
			}
			else{
				state = Lock;
			}
			break;
		case On_Release:
			if((arr[0] == 0x04) && (arr[1] == 0x01) && (arr[2] == 0x02) && (arr[3] == 0x01)){
				if(unlock == 0){
					state = Open;
					PORTB = 0x01;
					unlock = 1;
				}
				else{
					state = Lock;
					unlock = 0;
				}
			}
			else if((PINA & 0x00) == 0x00){
				state = On_Release;
			}
			else if((PINA & 0x04) == 0x04){
				hold = 0;
				arr[hold] = 4;
			}
			else{
				hold += 1;
				arr[hold] = (PINA | 0x00);
			}
			break;
		case Open:
			if((PINA & 0x80) == 0x80){
				state = Lock;
			}
			else if((PINA & 0x04) == 0x04){
				state = On_Release;
				hold = 0;
				arr[hold] = 4;
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
			PORTB = 0x00;
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
