#pragma once

#include "RTC_DS3232.h"
#include "Lcd_16X2.cpp"
#include "Alarm.h"
#include "Tone_Notes.h"
#include "Keys.h"
#include "Functions.h"

void setup();
void Main_Menu();
void Date_Time();                                                     // handling level-02 date/time sub menu
void Alarm_setting();                                                 // handling level-02 alarm setting sub menu
void Clock_Mode();                                                    // handling level-02 clock mode sub menu


void setup(){
	Key_Setup();
	RTC_Initialize();
	
	LCD_Initializer();
	
	LCD_SetCursor(0,2);
	LCD_String("LAB PROJECT");
	LCD_SetCursor(1,1);
	LCD_String(" ALARM CLOCK");
	_delay_ms(2000);
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
			PORTD |= (1 << 3);                    // Output 5 V to port Pin 7.
			Main_Menu();
			PORTD &= ~(1 << 3);                   // 0 V at port pin 7.
			}
		
		if(Alarm_Time()){                                     // check the alarm time with current time for activate the alarm
				
				int position= alarms[ha_count].Tone;
				LCD_Clear();
				LCD_SetCursor(0,3);
				LCD_String(" ALARM :");
				LCD_Num(ha_count+1);
				LCD_SetCursor(1,2);
				LCD_String(alarm_names[alarms[ha_count].Name]);
				
				if(position==0){key=ring_alarm(melody1);}
				else if(position==1){key=ring_alarm(melody2);}
				else if(position==2){key=ring_alarm(melody3);}
//				else if(position==3){key=ring_alarm(melody4);}
// 				else {key=ring_alarm(melody5);}
	
				if(key==1){
					// repeat mode analyzing 
					Repeat_Handle(ha_count);
					}
				else{
					// snooze analyzing
					if(alarms[ha_count].A_Time[1]<(60-snooze_time)){
						alarms[ha_count].A_Time[1]=alarms[ha_count].A_Time[1]+snooze_time;
					}
					else{
						alarms[ha_count].A_Time[1]=(alarms[ha_count].A_Time[1])%snooze_time;
						alarms[ha_count].A_Time[0]++;
					}
						
				}
				A_Sort();
				LCD_Clear();
		}
		else{
			Display_Time();                                     // Display the current Time and Date on display
		}	                                  
	}
}

void Main_Menu(){
	//main menu level-01 handling
	LCD_Clear();
	
	
	while(1){
		LCD_SetCursor(0,5);
		LCD_String("MAIN MENU");
		
		// date/time
		if(item[0]==0){
			LCD_SetCursor(1,2);
			LCD_String("DATE/TIME");
			Key_handle(3);
			
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
			LCD_String("ALARM SETTINGS");
			Key_handle(3);
			
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
			LCD_String("CLOCK MODE");
			Key_handle(3);
			
			if(level==1){continue;}
			else if(level==0){
				item[level]=0;
				LCD_Clear();
			return;}
			
			// Clock Mode level -02 handling
			Clock_Mode();
		}
		
		
	}
	
	LCD_Clear();
	
}

void Date_Time(){
	LCD_Clear();
	LCD_SetCursor(0,5);
	LCD_String("DATE/TIME");
	
	while(1){
		
		// Time
		if(item[1]==0){
			LCD_SetCursor(1,2);
			LCD_String("SET TIME");
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
				LCD_String("TIME CHANGED");
				LCD_SetCursor(1,3);
				LCD_String("SUCCESSFULLY");
				_delay_ms(300);
			}
			
			level=2;
			return;
		}
		
		// date
		else if(item[1]==1) {
			LCD_SetCursor(1,2);
			LCD_String("SET DATE");
			Key_handle(2);
			
			if(level==2){
			continue;}
			else if(level==1){
				item[level]=0;
				return;}
			
			if(Date_Set()){
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_String("DATE CHANGED");
				LCD_SetCursor(1,3);
				LCD_String("SUCCESSFULLY");
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
	LCD_SetCursor(0,2);
	LCD_String("ALARM SETTINGS");
	
	int count;
	
	while(1){
		// create alarm
		if(item[1]==0){
			LCD_SetCursor(1,2);
			LCD_String("CREATE ALARM");
			Key_handle(2);
			
			if(level==2){continue;}
			else if(level==1){
				item[level]=0;
				return;}
			
			for(count=0;count<6;count++){
				if(alarms[count].Alarm_state==0){
					if(Edit_Alarm(count)){
						alarm_t++;
						LCD_Clear();
						LCD_SetCursor(0,1);
						LCD_String("ALARM CREATED");
						LCD_SetCursor(1,1);
						//LCD_Num(count);
						LCD_String("SUCESSFULLY");
						
						A_Sort();
					}
					break;
				}   
			}
			
			if (count==6){
				LCD_Clear();
				LCD_SetCursor(0,1);
				LCD_String("CAN'T CREATE");
				LCD_SetCursor(1,5);
				LCD_String("ALARMS");
				_delay_ms(5000);
				
				item[1]=1;
			}
			
			level=2;
			return;
		}
		
		// Edit/Show alarm
		else if(item[1]==1) {
			LCD_SetCursor(1,2);
			LCD_String("EDIT/DELETE");
			Key_handle(3);
			
			if(level==2){
				continue;}
			else if(level==1){
				item[2]=0;
				return;}
				
				
			if(alarm_t==0){
				LCD_Clear();
				LCD_SetCursor(0,1);
				LCD_String("NO ALARMS TO");
				LCD_SetCursor(1,5);
				LCD_String("EDIT");
				_delay_ms(2000);
				
				LCD_Clear();
				LCD_SetCursor(0,1);
				LCD_String("NEW ALARM");
				LCD_SetCursor(1,5);
				LCD_String("CREATION");
				_delay_ms(3000);
				
				item[1]=0;
				continue;				
			}
			
			// continue with edit alarm
			count=0;
			while(alarms[count].Alarm_state==0){
				count=(count+1)%6;
			}
			 
			LCD_Clear();
			while(1){
				
				LCD_SetCursor(0,1);
				LCD_String("SELECT ALARM");
				LCD_SetCursor(1,0);
				LCD_String("ALARM :");
				LCD_Num(count+1);
				
				key =Key_Pressed();
				
				if(key==1){
					level++;
					LCD_Clear();
					while(1){
						
						LCD_SetCursor(0,1);
						LCD_String("ALARM :");
						LCD_Num(count+1);
						if (item[3]==0){
							LCD_SetCursor(1,3);
							LCD_String("EDIT ");
							
							Key_handle(2);
							
							if(level==4){
								continue;}
							else if(level==3){
								break;}
								
							Edit_Alarm(count);
							A_Sort();
							LCD_Clear();
							level=3;
							break;
						}
						else if(item[3]==1){
							LCD_SetCursor(1,3);
							LCD_String("DELETE");
							Key_handle(2);
							
							if(level==4){
								continue;}
							else if(level==3){
								break;}
							
							LCD_Clear();
							LCD_SetCursor(0,1);
							LCD_String("PROCEED WITH");
							LCD_SetCursor(1,3);
							LCD_String("DELETE?");
							//_delay_ms(2000);
							
							while(1){
								key=Key_Pressed();
								if(key==1){
									Delete_Alarm(count);
									LCD_Clear();
									LCD_SetCursor(0,1);
									LCD_String("SUCESSFULLY");
									LCD_SetCursor(1,3);
									LCD_String("DELETED");
									_delay_ms(2000);
									LCD_Clear();
									level=2;
									item[1]=0;
									return;
									//break;
									}
								else if(key==2){
									LCD_Clear();
									level=2;
									break;}
									
								//continue;
							}
							
						}
					}
				}
				else if(key==2){
					LCD_Clear();
					level--;
					break;
				}
				else if(key=3){
					while(alarms[count].Alarm_state==0){
						count=(count+1)%6;}
					continue;
				}
				else if(key==4){
					while(alarms[count].Alarm_state==0){
						count=(count-1+6)%6;}
					continue;
				}
				
			}
			
			LCD_Clear();
			return;
		}
		
		
		
		else if(item[1]==2) {
			LCD_SetCursor(1,2);
			LCD_String("DELETE ALL");
			Key_handle(3);
			
			if(level==2){
				continue;}
			else if(level==1){
				item[level]=0;
				return;}
			
			LCD_Clear();
			LCD_SetCursor(0,1);
			LCD_String("PROCEED WITH");
			LCD_SetCursor(1,3);
			LCD_String("DELETE?");
			//_delay_ms(2000);
			
			while(1){
				key=Key_Pressed();
				if(key==1){
					for(count=0;count<6;count++){
						if(alarms[count].Alarm_state){
							Delete_Alarm(count);}	
					}
					alarm_t=0;
					
					LCD_Clear();
					LCD_SetCursor(0,1);
					LCD_String("SUCESSFULLY");
					LCD_SetCursor(1,3);
					LCD_String("DELETED");
					_delay_ms(2000);
					LCD_Clear();
					
					//check
					item[1]=0;
					level=2;
					return;}
					//check
					
					
				else if(key==2){
					level--;
					break;}
				continue;
			}
			
			
			LCD_Clear();
			level=2;
			return;
		}
		
		
		
	}
}

void Clock_Mode(){
	LCD_Clear();
	LCD_SetCursor(0,1);
	LCD_String("CLOCK MODE");
	
	
	while(1){
		
		if(item[1]==0){
		LCD_SetCursor(1,1);
		LCD_String("24-HOUR");
		
		Key_handle(2);
		
		if(level==1){
			break;}
		else if(level==2){
			continue;}
			
		c_mode=1;
		LCD_Clear();
		LCD_SetCursor(0,1);
		LCD_String("24-HOUR MODE");
		LCD_SetCursor(1,3);
		LCD_String("SELECTED");
		_delay_ms(3000);
		
		LCD_Clear();
		level--;
		break;
		}
		
		if(item[1]==1){
			LCD_SetCursor(1,1);
			LCD_String("12-HOUR");
			
			Key_handle(2);
			
			if(level==1){
				item[1]=0;
				break;}
			else if(level==2){
				continue;}
			
			c_mode=0;
			LCD_Clear();
			LCD_SetCursor(0,1);
			LCD_String("12-HOUR MODE");
			LCD_SetCursor(1,3);
			LCD_String("SELECTED");
			_delay_ms(3000);
			
			LCD_Clear();
			level--;
			break;
		}
	}
}




