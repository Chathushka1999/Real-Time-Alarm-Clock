#include "RTC_DS3232.c"
#include "Lcd_16X2.c"
#include "Alarm.c"
#include "Keys.c"
#include "Functions.c"

void setup();
void Main_Menu();

void Date_Time();
void Alarm_setting();
void Clock_Mode();
void Reset_All();

void setup(){
	Key_Setup();
	RTC_Initialize();
	
	LCD_Initializer();
	
	LCD_SetCursor(0,2);
	LCD_String("LAB PROJECT");
	LCD_SetCursor(1,1);
	LCD_String(" ALARM CLOCK");
	_delay_ms(500);
	LCD_Clear();
}

int main()
{
	setup();
	
	while(1)
	{
		RTC_Get_Time(&rtc);	                                  // Get Date and time from DS3232 for refreshing the Time
		if (Key_Pressed()==1){                                // check the key pressing status go to the main menu
			level=level+1;
			Main_Menu();}
		
		if(Alarm_Time()){                                     // check the alarm time with current time for activate the alarm
			// alarm handling
			}
		else{
		Display_Time();}	                                  // Display the current Time and Date on display
	}
}

void Main_Menu(){
	//main menu level-01 handling
	LCD_Clear();
	LCD_SetCursor(0,5);
	LCD_String("Main Menu");
	
	while(1){
		// date/time
		if(item[0]==0){
			LCD_SetCursor(1,2);
			LCD_String("Date/Time");
			Key_handle(4);
			
			if(level==1){
			continue;}
			else if(level==0){
				item[level]=0;
				LCD_Clear();
			return;}
			
			// date/time level -02 handling
			Date_Time();
			}
		
		// alarm setting
		else if(item[0]==1){
			LCD_SetCursor(1,2);
			LCD_String("Alarm Settings");
			Key_handle(4);
			
			if(level==1){continue;}
			else if(level==0){
				item[level]=0;
				LCD_Clear();
			return;}
			
			// alarm setting level -02 handling
			Alarm_setting();
			}
		
		// clock mode changing
		else if(item[0]==2){
			LCD_SetCursor(1,2);
			LCD_String("Clock Mode");
			Key_handle(4);
			
			if(level==1){continue;}
			else if(level==0){
				item[level]=0;
				LCD_Clear();
			return;}
			
			// Clock Mode level -02 handling
			 Clock_Mode();
			 }
		
		// reset all settings
		else{
			LCD_SetCursor(1,2);
			LCD_String("Reset All");
			Key_handle(4);
			
			if(level==1){continue;}
			else if(level==0){
				item[level]=0;
				LCD_Clear();
			return;}
			
			// reset all level -02 handling
			Reset_All();
			}	
	}
	
	LCD_Clear();
	
}

void Date_Time(){
	LCD_Clear();
	LCD_SetCursor(0,5);
	LCD_String("Date/Time");
	
	while(1){
		
		// Time
		if(item[1]==0){
			LCD_SetCursor(1,2);
			LCD_String("Set Time");
			Key_handle(2);
			
			if(level==2){continue;}
			else if(level==1){
				item[level]=0;
				return;}
			
			if(Time_Set(rtc.hour, rtc.min)){
				rtc.hour=r_hour;
				rtc.min=r_min;
				RTC_Set_Time(&rtc);
				
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_String("Time Changed");
				LCD_SetCursor(1,3);
				LCD_String("Successfully");
				_delay_ms(300);
			}
			
			level=2;
			return;
		}
		
		// date
		else if(item[1]==1) {
			LCD_SetCursor(1,2);
			LCD_String("Set Date");
			Key_handle(2);
			
			if(level==2){
				continue;}
			else if(level==1){
				item[level]=0;
				return;}
			
			if(Date_Set()){
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_String("Date Changed");
				LCD_SetCursor(1,3);
				LCD_String("Successfully");
				_delay_ms(300);
			}

			LCD_Clear();
			level=2;
			return;
		}
		
	}		
}
void Alarm_setting(){
	LCD_Clear();
	LCD_SetCursor(0,5);
	LCD_String("Alarm Settings");
	
	while(1){
		// create alarm
		if(item[1]==0){
			LCD_SetCursor(1,2);
			LCD_String("Create Alarm");
			Key_handle(2);
			
			if(level==2){continue;}
			else if(level==1){
				item[level]=0;
			return;}
			
			
			level=2;
			return;
		}
		
		// Edit alarm
		else if(item[1]==1) {
			LCD_SetCursor(1,2);
			LCD_String("Edit Alarm");
			Key_handle(2);
			
			if(level==2){
			continue;}
			else if(level==1){
				item[level]=0;
			return;}
			
			
			
			LCD_Clear();
			level=2;
			return;
		}
		
		
		
	}
}
void Clock_Mode(){
	
}
void Reset_All(){
	
}



