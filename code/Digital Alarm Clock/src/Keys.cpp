#include "Keys.h"


void Key_Setup(){
	DDRB = 0b00000000;                                         // set the push button pins as input mode
	PORTB = 0b01111100;
}



int Key_Pressed(){
	int debounce_time=700;
	int s_debounce_time=700; 
	
	if(!(PINB & (1<<5))){
		_delay_ms(debounce_time);
		return 1;}
	else if(!(PINB & (1<<6))){
		_delay_ms(debounce_time);
		return 2;}
	else if(!(PINB & (1<<3))){
		_delay_ms(s_debounce_time);
		return 3;}
	else if(!(PINB & (1<<4))){
		_delay_ms(s_debounce_time);
		return 4;}
	else{return 0;}
}






