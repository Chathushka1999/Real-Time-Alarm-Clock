#include <Keypad.h>

int number_Led = 4;
int reset_Led = 5;
int scroll_Led = 6;



const byte ROWS = 4; 
const byte COLS = 3; 

  
  /* define the symbols on the buttons of the keypads */
char Keys[ROWS][COLS] = 
  {
    {1,2,3},
    {4,5,6},
    {7,8,9},
    {10,12,11}
  };   



byte rowPins[ROWS] = {10,9,8,7}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {11,12,13}; /* connect to the column pinouts of the keypad */



  

/* initialize an instance of class NewKeypad */
Keypad cKeypad = Keypad( makeKeymap(Keys), rowPins, colPins, ROWS, COLS); 



void setup()
{
  Serial.begin(9600);


  
  pinMode(10, INPUT);
  pinMode(9, INPUT);
  pinMode(8, INPUT);
  pinMode(7, INPUT);
  
  pinMode(reset_Led, OUTPUT);
  pinMode(scroll_Led, OUTPUT);
  pinMode(number_Led, OUTPUT);


}





void loop()
{


 char p_key = cKeypad.getKey();
//Numerical key parts
  if (p_key<10)
  {
    for (int i=0;i<p_key;i++)
    {
      digitalWrite(number_Led, HIGH) ;
      delay(300) ;
      digitalWrite(number_Led, LOW) ;
      delay(300);
    }
  }



//Reset Button
  else if (p_key==10)
  {
    digitalWrite(reset_Led, HIGH) ;
    delay(500) ;
    digitalWrite(reset_Led, LOW) ;
  }

//Scroll Bar
  else if (p_key==11)
  {
    digitalWrite(scroll_Led, HIGH) ;
    delay(500) ;
    digitalWrite(scroll_Led, LOW) ;
  }
    
//dealing with key zero
  else if (p_key==12)
  {
    digitalWrite(number_Led, HIGH);
    digitalWrite(reset_Led,HIGH) ;
    delay(500) ;
    digitalWrite(number_Led, LOW) ;
    digitalWrite(reset_Led,LOW) ;
  }
}
