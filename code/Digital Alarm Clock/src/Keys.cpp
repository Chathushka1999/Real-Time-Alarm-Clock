#include "Keys.h"


void Key_Setup(){
	DDRB = 0b00000000;                                         // set the push button pins as input mode
	PORTB = 0b00111110;
}



int Key_Pressed(){
	int debounce_time=500;
	int s_debounce_time=300; 
	
	if(!(PINB & (1<<4))){
		_delay_ms(debounce_time);
		return 1;}
	else if(!(PINB & (1<<5))){
		_delay_ms(debounce_time);
		return 2;}
	else if(!(PINB & (1<<3))){
		_delay_ms(s_debounce_time);
		return 3;}
	else if(!(PINB & (1<<2))){
		_delay_ms(s_debounce_time);
		return 4;}
	else{return 0;}
}



// Handling key presses across level and items
void Key_handle(int n,int* ITEM, int* LEVEL){

	int k_key= Key_Pressed();

	if (k_key==1){
		*LEVEL+=1;
		LCD_Clear();}
	else if(k_key==2){
		*LEVEL-=1;
		LCD_Clear();	}
	else if(k_key==3){
		ITEM[*LEVEL-1]=(ITEM[*LEVEL-1]+1)%n;
		LCD_SetCursor(1,0);
		LCD_String("                ");}
	else if(k_key==4){
		ITEM[*LEVEL-1]=(ITEM[*LEVEL-1]-1+n)%n;
		LCD_SetCursor(1,0);
		LCD_String("                ");}

	return ;
	
}

