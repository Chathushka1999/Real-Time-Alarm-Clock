#include "Time.h"


/*Getting input the current time... and get user input for clock time in a sequential manner as minute--> hour and return */
int Time_Set()
{
	RTC_Get_Time(&t_rtc);
	//keeping reference to the change rather than changing at once
	uint8_t r_hour = t_rtc.hour, r_min = t_rtc.min;
	//variable for hadling key pressed inside the function Time_Set
	int t_key = 0;

	LCD_Clear();
	LCD_SetCursor(0, 1);
	LCD_String("UPDATE TIME");
	LCD_SetCursor(1, 3);
	LCD_TwoDigit(r_hour);
	LCD_String(":");
	LCD_TwoDigit(r_min);

	while (1)
	{
		LCD_SetCursor(1, 3);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1, 3);
		LCD_TwoDigit(r_hour);
		_delay_ms(100);

		t_key = Key_Pressed();
		if (t_key == 1)
		{
			break;
		}
		else if (t_key == 2)
		{
			return 0;
		}
		else if (t_key == 3)
		{
			r_hour = (r_hour + 1) % 24;
		}
		else if (t_key == 4)
		{
			r_hour = (r_hour - 1 + 24) % 24;
		}
	}

	while (1)
	{
		LCD_SetCursor(1, 6);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1, 6);
		LCD_TwoDigit(r_min);
		_delay_ms(100);

		t_key = Key_Pressed();
		if (t_key == 1)
		{
			//update time sucessfully and return 1 to indicate functions happened successufully
			t_rtc.hour=r_hour;
			t_rtc.min=r_min;
			return 1;
		}
		else if (t_key == 2)
		{
			return 0;
		}
		else if (t_key == 3)
		{
			r_min = (r_min + 1) % 60;
		}
		else if (t_key == 4)
		{
			r_min = (r_min - 1 + 60) % 60;
		}
	}
}

/* intended to handle the editing date... This functionality only for clock time */
int Date_Set()
{
	//variable for handling key press inside the function
	int d_key=0;
	int r_date = t_rtc.date;
	int r_month = t_rtc.month;
	int r_year = t_rtc.year + 2000;
	int days;

	LCD_Clear();
	LCD_SetCursor(0, 1);
	LCD_String("UPDATE DATE");
	LCD_SetCursor(1, 3);
	LCD_TwoDigit(r_date);
	LCD_String(":");
	LCD_TwoDigit(r_month);
	LCD_String(":");
	LCD_Num(r_year);

	while (1)
	{
		LCD_SetCursor(1, 9);
		LCD_String("    ");
		_delay_ms(100);
		LCD_SetCursor(1, 9);
		LCD_Num(r_year);
		_delay_ms(100);

		d_key = Key_Pressed();

		if (d_key == 1)
		{
			break;
		}
		else if (d_key == 2)
		{
			return 0;
		}
		else if (d_key == 3)
		{
			r_year = (r_year + 1);
		}
		else if (d_key == 4)
		{
			r_year = (r_year - 1);
		}
	}

	while (1)
	{
		LCD_SetCursor(1, 6);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1, 6);
		LCD_TwoDigit(r_month);
		_delay_ms(100);

		d_key = Key_Pressed();

		if (d_key == 1)
		{
			break;
		}
		else if (d_key == 2)
		{
			return 0;
		}
		else if (d_key == 3)
		{
			r_month = (r_month + 1) % 12;
		}
		else if (d_key == 4)
		{
			r_month = (r_month - 1 + 12) % 12;
		}
	}


	int months[12]={31,29,31,30,31,30,31,31,30,31,30,31}; 
	days = months[r_month - 1];

	while (1)
	{

		LCD_SetCursor(1, 3);
		LCD_String("  ");
		_delay_ms(100);
		LCD_SetCursor(1, 3);
		LCD_TwoDigit(r_date);
		_delay_ms(100);

		d_key = Key_Pressed();

		if (d_key == 1)
		{

			t_rtc.date = r_date;
			t_rtc.month = r_month;
			t_rtc.year = r_year - 2000;

			RTC_Set_Time(&t_rtc);
			return 1;
		}
		else if (d_key == 2)
		{
			return 0;
		}
		else if (d_key == 3)
		{
			r_date = (r_date + 1) % days;
		}
		else if (d_key == 4)
		{
			r_date = (r_date - 1 + days) % days;
		}
	}
}

void Date_Time(int* LEVEL, int* ITEM)
{
	LCD_Clear();
	LCD_SetCursor(0, 5);
	LCD_String("DATE/TIME");

	while (1)
	{

		// Time(level=2)
		if (ITEM[1] == 0)
		{
			LCD_SetCursor(1, 2);
			LCD_String("SET TIME");
			Key_handle(2, ITEM, LEVEL);

			if (*LEVEL == 2)
			{
				continue;
			}
			else if (*LEVEL == 1)
			{
				ITEM[*LEVEL] = 0;
				return;
			}

			//level 3 hadling of Time set
			if (Time_Set())
			{
				RTC_Set_Time(&t_rtc);

				LCD_Clear();
				LCD_SetCursor(0, 0);
				LCD_String("TIME CHANGED");
				LCD_SetCursor(1, 3);
				LCD_String("SUCCESSFULLY");
				_delay_ms(300);
			}

			*LEVEL = 2;
			return;
		}

		// date(level=2)
		else if (ITEM[1] == 1)
		{
			LCD_SetCursor(1, 2);
			LCD_String("SET DATE");
			Key_handle(2, ITEM, LEVEL);

			if (*LEVEL == 2)
			{
				continue;
			}
			else if (*LEVEL == 1)
			{
				ITEM[*LEVEL] = 0;
				return;
			}

			if (Date_Set())
			{
				LCD_Clear();
				LCD_SetCursor(0, 0);
				LCD_String("DATE CHANGED");
				LCD_SetCursor(1, 3);
				LCD_String("SUCCESSFULLY");
				_delay_ms(300);
			}

			LCD_Clear();
			*LEVEL = 2;
			return;
		}
	}
}



