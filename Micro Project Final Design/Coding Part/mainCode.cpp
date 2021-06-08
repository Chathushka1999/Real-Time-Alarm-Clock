// Analysing Input....
#ifndef F_CPU
#define F_CPU 8000000UL // 8 MHz clock speed
#endif


// Including libraries
#include <avr/io.h>
#include <util/delay.h>

//defining Key inputs...
#define nextKey 0b00001000
#define preKey 0b00010000
#define okKey 0b00000100
#define menuKey 0b00000010
#define resetKey 0b01000000

// Defining required outputs...
#define OFF 0b00000000
#define nextO 0b00100000
#define preO 0b00010000
#define okO 0b00001000
#define menuO 0b00000100
#define resetO 0b00000010
#define alarmO 0b00000001


//defining debounce times to avoid bouncing of keys
int debounceTime = 500;
int debounceTimeScroll = 300;


int main(void)
{
	DDRB = 0xFF;        //Makes PortB as output
	DDRD = 0x00;		  //Makes PortD as input
	
	// Checking everything correctly initiated....
	PORTB = 0xFF;
	_delay_ms(5000);
	PORTB = 0x00;
	
	PIND = 0x00;
	
	
	while(1) //infinite loop
	{
		keyPressed();
	}
}



void keyPressed()
{
	
	//Checking keys....
	if (PIND==nextKey)
	{
		PORTB = nextO;
		_delay_ms(debounceTimeScroll);
		PORTB = OFF;
	}
	else if (PIND == preKey)
	{
		PORTB = preO;
		_delay_ms(debounceTimeScroll);
		PORTB = OFF;
	}
	else if (PIND == resetKey)
	{
		PORTB = resetO;
		_delay_ms(debounceTime)
		PORTB = OFF;
	}
	else if (PIND == resetKey)
	{
		PORTB = resetO;
		_delay_ms(debounceTime)
		PORTB = OFF;
	}
	else if (PIND == menuKey)
	{
		PORTB = menuO;
		_delay_ms(debounceTime)
		PORTB = OFF;
	}
	else if (PIND == okKey)
	{
		PORTB = okO;
		_delay_ms(debounceTime)
		PORTB = OFF;
	}
	else
	{
		PORTB = alarmO;
		_delay_ms(debounceTime)
		PORTB = OFF;
	}
}