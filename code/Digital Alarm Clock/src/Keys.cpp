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

int* Key_handle(int n,int k_item[5]){

	int k_key= Key_Pressed();
	int k_level=k_item[4];

	if (k_key==1){
		k_level++;
		LCD_Clear();}
	else if(k_key==2){
		k_level--;
		LCD_Clear();	}
	else if(k_key==3){
		k_item[k_level-1]=(k_item[k_level-1]+1)%n;
		LCD_SetCursor(1,0);
		LCD_String("                ");}
	else if(k_key==4){
		k_item[k_level-1]=(k_item[k_level-1]-1+n)%n;
		LCD_SetCursor(1,0);
		LCD_String("                ");}


	k_item[4]=k_level;
	return k_item;
}




