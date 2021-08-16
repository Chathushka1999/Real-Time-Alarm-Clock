#include "Functions.h"



int Time_Set(uint8_t hour, uint8_t min){
	
	r_hour=hour,r_min =min;
	key=0;
	
	
	
	LCD_Clear();
	LCD_SetCursor(0,1);
	LCD_String("UPDATE TIME");
	LCD_SetCursor(1,3);
	LCD_TwoDigit(r_hour);
	LCD_String(":");
	LCD_TwoDigit(r_min);
	
	while(1){
		LCD_SetCursor(1,3);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1,3);
		LCD_TwoDigit(r_hour);
		_delay_ms(100);
		
		
		key=Key_Pressed();
		if (key==1){
		break;	}
		else if (key==2){return 0;}
		else if(key==3){
		r_hour=(r_hour+1)%24;}
		else if(key==4){
			r_hour=(r_hour-1+24)%24;
		}
	}
	
	while(1){
		LCD_SetCursor(1,6);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1,6);
		LCD_TwoDigit(r_min);
		_delay_ms(100);
		
		
		key=Key_Pressed();
		if (key==1){
			//update time
			// 				hour = r_hour;
			// 				min  = r_min;
		return 1;	}
		else if (key==2){return 0;}
		else if(key==3){
		r_min=(r_min+1)%60;}
		else if(key==4){
			r_min=(r_min-1+60)%60;
		}
		
		
		
		
	}
}

int Date_Set(){
	
	int r_date = rtc.date;
	int r_month = rtc.month;
	int r_year =rtc.year+2000;
	int days;
	
	LCD_Clear();
	LCD_SetCursor(0,1);
	LCD_String("UPDATE DATE");
	LCD_SetCursor(1,3);
	LCD_TwoDigit(r_date);
	LCD_String(":");
	LCD_TwoDigit(r_month);
	LCD_String(":");
	LCD_Num(r_year);
	
	while(1){
		LCD_SetCursor(1,9);
		LCD_String("    ");
		_delay_ms(100);
		LCD_SetCursor(1,9);
		LCD_Num(r_year);
		_delay_ms(100);
		
		
		key=Key_Pressed();
		
		if (key==1){
		break;	}
		else if (key==2){return 0;}
		else if(key==3){
		r_year=(r_year+1);}
		else if(key==4){
		r_year=(r_year-1);}
	}
	
	while(1){
		LCD_SetCursor(1,6);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1,6);
		LCD_TwoDigit(r_month);
		_delay_ms(100);
		
		
		key=Key_Pressed();
		
		if (key==1){
		break;	}
		else if (key==2){return 0;}
		else if(key==3){
		r_month=(r_month+1)%12;}
		else if(key==4){
		r_month=(r_month-1+12)%12;}
	}
	
	days=months[r_month-1];
	
	while(1){
		
		LCD_SetCursor(1,3);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1,3);
		LCD_TwoDigit(r_date);
		_delay_ms(100);
		
		key=Key_Pressed();
		
		
		if (key==1){
			
			rtc.date=r_date;
			rtc.month=r_month;
			rtc.year=r_year-2000;
			
			RTC_Set_Time(&rtc);
			return 1;
		}
		else if (key==2){return 0;}
		else if(key==3){
		r_date=(r_date+1)%days;}
		else if(key==4){
		r_date=(r_date-1+days)%days;}
	}
	
	
	
}

int A_Abort(){
	LCD_Clear();
	LCD_SetCursor(0,3);
	LCD_String("PROCEED ");
	LCD_SetCursor(1,0);
	LCD_String("WITHOUT SAVE?");
	
	
	while(1){
		key=Key_Pressed();
		if(key==1){
		return 1;}
		else if(key==2){
		return 0;}
	}
	
	
}

int Edit_Alarm(int count){
	LCD_Clear();
	LCD_SetCursor(0,2);
	LCD_String("UPDATE NAME");
	LCD_SetCursor(1,2);
	LCD_String(alarm_names[alarms[count].Name]);
	
	while(1){
		LCD_SetCursor(1,2);
		LCD_String(alarm_names[alarms[count].Name]);
		_delay_ms(100);
		LCD_SetCursor(1,2);
		LCD_String("               ");
		_delay_ms(100);
		
		key=Key_Pressed();
		
		if (key==1){
		break;}
		else if (key==2){
		return 0;}
		else if(key==3){
		alarms[count].Name=(alarms[count].Name+1)%6;}
		else if(key==4){
		alarms[count].Name=(alarms[count].Name-1+6)%6;}
	}
	
	if((Time_Set(alarms[count].A_Time[0],alarms[count].A_Time[1]))){
		alarms[count].A_Time[0]=r_hour;
		alarms[count].A_Time[1]=r_min;
	}
	else{return 0;}
	
	LCD_Clear();
	LCD_SetCursor(0,2);
	LCD_String("UPDATE TONE");
	LCD_SetCursor(1,2);
	LCD_String(alarm_tones[alarms[count].Tone]);
	
	while(1){
		LCD_SetCursor(1,2);
		LCD_String(alarm_tones[alarms[count].Tone]);
		_delay_ms(100);
		LCD_SetCursor(1,2);
		LCD_String("               ");
		_delay_ms(100);
		
		key=Key_Pressed();
		
		if (key==1){
		break;}
		else if (key==2){
		return 0;}
		else if(key==3){
		alarms[count].Tone=(alarms[count].Tone+1)%3;}
		else if(key==4){
		alarms[count].Tone=(alarms[count].Tone-1+3)%3;}
	}
	
	
	LCD_Clear();
	LCD_SetCursor(0,2);
	LCD_String("REPEAT STATE");
	LCD_SetCursor(1,2);
	LCD_String(repeat_state[alarms[count].Repeat_state]);
	
	while(1){
		LCD_SetCursor(1,2);
		LCD_String(repeat_state[alarms[count].Repeat_state]);
		_delay_ms(100);
		LCD_SetCursor(1,2);
		LCD_String("               ");
		_delay_ms(100);
		
		key=Key_Pressed();
		
		if (key==1){
		break;}
		else if (key==2){
			return 0;}
		else if(key==3){
		alarms[count].Repeat_state=(alarms[count].Repeat_state+1)%3;}
		else if(key==4){
		alarms[count].Repeat_state=(alarms[count].Repeat_state-1+3)%3;}
	}
	
	alarms[count].Alarm_state=1;
	
	alarms[count].Date[0]=rtc.date;
	alarms[count].Date[1]=rtc.month;
	alarms[count].Date[2]=rtc.year;
	
	return 1;
	
}

void  Day_Increament(int count){
	int n_date=alarms[count].Date[0]+1;
	int n_month =alarms[count].Date[1];
	int n_year=alarms[count].Date[2];
	
	if(n_date>months[n_month-1]){
		n_date=1;
		n_month++;
		
		if(n_month>12){
			n_month=1;
			n_year++;
		}
	}
	alarms[count].Date[0]=n_date;
	alarms[count].Date[1]=n_month;
	alarms[count].Date[2]=n_year;
	
	
	
	return;
	
}

int Compare(int a, int b){
	if(a==b){
	return 1;}
	else if(a>b){
	return 0;}
	else{
		return 2;
	}
}

int Time_Compare(struct Alarm A, struct Alarm B){
	
	//compare year
	key=Compare(A.Date[2],B.Date[2]);
	
	if(key==0){
	return 0;}
	if(key==2){
	return 2;}
	
	//compare month
	key=Compare(A.Date[1],B.Date[1]);
	
	if(key==0){
	return 0;}
	if(key==2){
	return 2;}
	
	// compare date
	key=Compare(A.Date[0],B.Date[0]);
	
	if(key==0){
	return 0;}
	if(key==2){
	return 2;}
	
	// compare hour
	key=Compare(A.A_Time[0],B.A_Time[0]);
	
	if(key==0){
	return 0;}
	if(key==2){
	return 2;}
	
	// compare min
	key=Compare(A.A_Time[1],B.A_Time[1]);
	
	if(key==0){
	return 0;}
	if(key==2){
	return 2;}
	
	return 1;
	
}

void A_Sort(){
	h_alarm.A_Time[0]=0;
	h_alarm.A_Time[1]=0;
	h_alarm.Date[0]=1;
	h_alarm.Date[1]=1;
	h_alarm.Date[2]=2040;
	
	// assign current date and time to clock
	Clock.Date[0]=rtc.date;
	Clock.Date[1]=rtc.month;
	Clock.Date[2]=rtc.year;
	Clock.A_Time[0]=rtc.hour;
	Clock.A_Time[1]=rtc.min;

	
	for (int count=0; count<6;count++){
		if(alarms[count].Alarm_state){
			int key=Time_Compare(Clock,alarms[count]);
			if(key==1){
				alarms[count].Alarm_state=0;
				alarm_t--;
				continue;}
			else if(key==0){
				Day_Increament(count);}
			
			if(Time_Compare(h_alarm,alarms[count])==0){
				h_alarm=alarms[count];
				ha_count=count;}
		}
		

		
	}
	
	return ;
	
}

int Alarm_Time(){
	
	
	C_Time.Date[0]=rtc.date;
	C_Time.Date[1]=rtc.month;
	C_Time.Date[2]=rtc.year;
	C_Time.A_Time[0]=rtc.hour;
	C_Time.A_Time[1]=rtc.min;
	//Alarm time
	if(Time_Compare(C_Time,alarms[ha_count])==1){
		return 1;}
		
	return 0;
}

void Delete_Alarm(int count){
	alarms[count].Alarm_state=0;
	alarm_t--;
	A_Sort();
}

void Repeat_Handle(int posi){
	
	int rs_state=alarms[posi].Repeat_state;
	if(rs_state==0){
		alarms[posi].Alarm_state=0;	}
	else if(rs_state==1){
		Day_Increament(posi);
	}
	else{
		for(int i=0;i<7;i++){
			Day_Increament(posi);
		}
		
	}
}
