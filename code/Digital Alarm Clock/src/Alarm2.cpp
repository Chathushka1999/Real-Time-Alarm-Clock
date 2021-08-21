#include "Alarm2.h"

/* variables */
//keep the track of number of true alarms
int alarm_t = 0;
//snooze time
int snooze_time = 1;
//index reference for the first alarm
int ha_count = 0;

//alarm parameters
char alarm_names[6][12] = {"MORNING", "EVENING", "NIGNT", "NAP-ALARM", "WORK-ALARM", "NOISY"};
char alarm_tones[5][12] = {"MELODY", "STRANGE", "LOVELY", "ROCK", "POP"};
char repeat_state[4][12] = {"ONCE", "DAILY", "WEEKLY"};

//keeping track of current time in alarm format
Alarm c_time;
//reference for the first alarm
Alarm h_alarm;
//Creating Alarm class for Handling six alarms
Alarm alarms[6];

/* Things come under notes */
int melody1[102] = {50,200,
	NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
	NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_DS4,16, NOTE_F4,16,
	NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
	NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16, NOTE_G4,8, NOTE_C4,8, NOTE_E4,16, NOTE_F4,16,
	NOTE_G4,-4, NOTE_C4,-4,NOTE_DS4,16, NOTE_F4,16, NOTE_G4,4, NOTE_C4,4, NOTE_DS4,16, NOTE_F4,16,
	NOTE_D4,-1,NOTE_F4,-4, NOTE_AS3,-4,NOTE_DS4,16, NOTE_D4,16, NOTE_F4,4, NOTE_AS3,-4,
	NOTE_DS4,16, NOTE_D4,16, NOTE_C4,-1
};

int melody2[170] = {84,140,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //1
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //5
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8, //9
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_B2, 8, NOTE_C3, 8,
	NOTE_E2, 8, NOTE_E2, 8, NOTE_E3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_D3, 8, NOTE_E2, 8, NOTE_E2, 8,
	NOTE_C3, 8, NOTE_E2, 8, NOTE_E2, 8, NOTE_AS2, -2
};

// Asa branca - Luiz Gonzaga
int melody3[186] ={92,120,
	NOTE_G4,8, NOTE_A4,8, NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_B4,4,
	NOTE_C5,4, NOTE_C5,2, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, NOTE_D5,4, NOTE_C5,4,

	NOTE_B4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,
	NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,

	NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
	NOTE_G4,2, REST,8, NOTE_G4,8, NOTE_G4,8, NOTE_A4,8,
	NOTE_B4,4, NOTE_D5,4, REST,8, NOTE_D5,8, NOTE_C5,8, NOTE_B4,8,

	NOTE_G4,4, NOTE_C5,4, REST,8, NOTE_C5,8, NOTE_B4,8, NOTE_A4,8,
	NOTE_A4,4, NOTE_B4,4, REST,8, NOTE_B4,8, NOTE_A4,8, NOTE_G4,8,
	NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,

	NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
	NOTE_G4,4, NOTE_F5,8, NOTE_D5,8, NOTE_E5,8, NOTE_C5,8, NOTE_D5,8, NOTE_B4,8,
	NOTE_C5,8, NOTE_A4,8, NOTE_B4,8, NOTE_G4,8, NOTE_A4,8, NOTE_G4,8, NOTE_E4,8, NOTE_G4,8,
	NOTE_G4,-2, REST,4
	
};

// Baby Elephant Walk
int melody4[144] = { 71,132,
	NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
	NOTE_FS4,8, NOTE_G4,8, REST,4, REST,2,
	NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
	NOTE_G4,-2, NOTE_A4,8, NOTE_DS4,1,
	
	NOTE_A4,8,
	NOTE_E4,8, NOTE_C4,8, REST,4, REST,2,
	NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
	NOTE_FS4,8, NOTE_G4,8, REST,4, REST,4, REST,8, NOTE_G4,8,
	NOTE_D5,4, NOTE_D5,4, NOTE_B4,8, NOTE_G4,8, REST,8, NOTE_G4,8,
	
	NOTE_C5,4, NOTE_C5,4, NOTE_AS4,16, NOTE_C5,16, NOTE_AS4,16, NOTE_G4,16, NOTE_F4,8, NOTE_DS4,8,
	NOTE_FS4,4, NOTE_FS4,4, NOTE_F4,16, NOTE_G4,16, NOTE_F4,16, NOTE_DS4,16, NOTE_C4,8, NOTE_G4,8,
	NOTE_AS4,8, NOTE_C5,8, REST,4, REST,2,
};

//Odetojay
int melody5[126] = { 62,114,
	NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,
	NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
	NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
	NOTE_E4,-4, NOTE_D4,8,  NOTE_D4,2,

	NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,
	NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
	NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
	NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2,

	NOTE_D4,4,  NOTE_D4,4,  NOTE_E4,4,  NOTE_C4,4,
	NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_C4,4,
	NOTE_D4,4,  NOTE_E4,8,  NOTE_F4,8,  NOTE_E4,4, NOTE_D4,4,
	NOTE_C4,4,  NOTE_D4,4,  NOTE_G3,2,

	NOTE_E4,4,  NOTE_E4,4,  NOTE_F4,4,  NOTE_G4,4,
	NOTE_G4,4,  NOTE_F4,4,  NOTE_E4,4,  NOTE_D4,4,
	NOTE_C4,4,  NOTE_C4,4,  NOTE_D4,4,  NOTE_E4,4,
	NOTE_D4,-4,  NOTE_C4,8,  NOTE_C4,2
	
};

/*Getting input the current time... and get user input for clock time in a sequential manner as minute--> hour and return */
int alarm_Time_Set(int num)
{
    //keeping reference to the change rather than changing at once
    uint8_t r_hour = alarms[num].A_Time[0], r_min = alarms[num].A_Time[1];
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
            alarms[num].A_Time[0] = r_hour;
            alarms[num].A_Time[1] = r_min;
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

/* comparing current time with alarm time and if the time is same set the
 alarm state as flase... If the alarm lag the current time set the alarm to 
 next day...  compare state true alarms and sort out h_alarm as the first alarm */
void A_Sort()
{
    h_alarm.A_Time[0] = 0;
    h_alarm.A_Time[1] = 0;
    h_alarm.Date[0] = 1;
    h_alarm.Date[1] = 1;
    h_alarm.Date[2] = 2040;

    // assign current date and time to clock
    rtc_t a_rtc;
    RTC_Get_Time(&a_rtc);
    c_time.Date[0] = a_rtc.date;
    c_time.Date[1] = a_rtc.month;
    c_time.Date[2] = a_rtc.year;
    c_time.A_Time[0] = a_rtc.hour;
    c_time.A_Time[1] = a_rtc.min;

    for (int count = 0; count < 6; count++)
    {
        if (alarms[count].Alarm_state)
        {
            int key = Time_Compare(c_time, alarms[count]);
            if (key == 1)
            {
                alarms[count].Alarm_state = 0;
                alarm_t--;
                continue;
            }
            else if (key == 0)
            {
                Day_Increament(count);
            }

            if (Time_Compare(h_alarm, alarms[count]) == 0)
            {
                h_alarm = alarms[count];
                ha_count = count;
            }
        }
    }

    return;
}

/* This function is intended to create handle the recurring state of the alarm 
that set to off */
void Repeat_Handle(int posi)
{

    int rs_state = alarms[posi].Repeat_state;
    if (rs_state == 0)
    {
        alarms[posi].Alarm_state = 0;
        alarm_t-=1;
    }
    else if (rs_state == 1)
    {
        Day_Increament(posi);
    }
    else
    {
        for (int i = 0; i < 7; i++)
        {
            Day_Increament(posi);
        }
    }
}

/*comparing current time from rtc and and head alarm time and return 1 when 
they are same and return 0 otherwiswe*/
int Alarm_Time()
{
    rtc_t a_rtc;
    RTC_Get_Time(&a_rtc);
    c_time.Date[0] = a_rtc.date;
    c_time.Date[1] = a_rtc.month;
    c_time.Date[2] = a_rtc.year;
    c_time.A_Time[0] = a_rtc.hour;
    c_time.A_Time[1] = a_rtc.min;
    //Alarm time
    if (alarm_t>0){
    if (Time_Compare(c_time, alarms[ha_count]) == 1)
        {   
            return 1;
        }
    }
    return 0;
}

/*This function will change the alarm state of the alarm given as input to false
and decrease the count true alarms by 1*/
void Delete_Alarm(int alarm_num)
{
    alarms[alarm_num].Alarm_state = 0;
    alarm_t -= 1;
    A_Sort();
}

/* Function intended to handle the probelm during the increasing of date
(increasing date if its last day of month and increasing year if its 
last day of the year) */
void Day_Increament(int count)
{
    int n_date = alarms[count].Date[0] + 1;
    int n_month = alarms[count].Date[1];
    int n_year = alarms[count].Date[2];

    int a_month[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (n_date > a_month[n_month - 1])
    {
        n_date = 1;
        n_month++;

        if (n_month > 12)
        {
            n_month = 1;
            n_year++;
        }
    }
    alarms[count].Date[0] = n_date;
    alarms[count].Date[1] = n_month;
    alarms[count].Date[2] = n_year;

    return;
}

/*Function to compare two elements of type int*/
int Compare(int a, int b)
{
    if (a == b)
    {
        return 1;
    }
    else if (a > b)
    {
        return 0;
    }
    else
    {
        return 2;
    }
}

/* Comparing two times in the struct format alarm and return 0 if first element
big or return 1 if both elements are same length.. and 2 if second element is big
Here we used the comparing algorithm in the format of year --> month --> date--> min*/
int Time_Compare(struct Alarm A, struct Alarm B)
{
    // c_key used to have a track of key pressed
    int c_key = 0;
    //compare year
    c_key = Compare(A.Date[2], B.Date[2]);

    if (c_key == 0)
    {
        return 0;
    }
    if (c_key == 2)
    {
        return 2;
    }

    //compare month
    c_key = Compare(A.Date[1], B.Date[1]);

    if (c_key == 0)
    {
        return 0;
    }
    if (c_key == 2)
    {
        return 2;
    }

    // compare date
    c_key = Compare(A.Date[0], B.Date[0]);

    if (c_key == 0)
    {
        return 0;
    }
    if (c_key == 2)
    {
        return 2;
    }

    // compare hour
    c_key = Compare(A.A_Time[0], B.A_Time[0]);

    if (c_key == 0)
    {
        return 0;
    }
    if (c_key == 2)
    {
        return 2;
    }

    // compare min
    c_key = Compare(A.A_Time[1], B.A_Time[1]);

    if (c_key == 0)
    {
        return 0;
    }
    if (c_key == 2)
    {
        return 2;
    }

    return 1;
}

/*This function intended to change the parameters of alarm during the edit
alarm operation*/
int Edit_Alarm(int count)
{
    int ea_key;
    LCD_Clear();
    LCD_SetCursor(0, 2);
    LCD_String("UPDATE NAME");
    LCD_SetCursor(1, 2);
    LCD_String(alarm_names[alarms[count].Name]);

    while (1)
    {
        LCD_SetCursor(1, 2);
        LCD_String(alarm_names[alarms[count].Name]);
        _delay_ms(100);
        LCD_SetCursor(1, 2);
        LCD_String("               ");
        _delay_ms(100);

        ea_key = Key_Pressed();

        if (ea_key == 1)
        {
            break;
        }
        else if (ea_key == 2)
        {
            return 0;
        }
        else if (ea_key == 3)
        {
            alarms[count].Name = (alarms[count].Name + 1) % 6;
        }
        else if (ea_key == 4)
        {
            alarms[count].Name = (alarms[count].Name - 1 + 6) % 6;
        }
    }

    if (!(alarm_Time_Set(count)))
    {
        return 0;
    }

    LCD_Clear();
    LCD_SetCursor(0, 2);
    LCD_String("UPDATE TONE");
    LCD_SetCursor(1, 2);
    LCD_String(alarm_tones[alarms[count].Tone]);

    while (1)
    {
        LCD_SetCursor(1, 2);
        LCD_String(alarm_tones[alarms[count].Tone]);
        _delay_ms(100);
        LCD_SetCursor(1, 2);
        LCD_String("               ");
        _delay_ms(100);

        ea_key = Key_Pressed();

        if (ea_key == 1)
        {
            break;
        }
        else if (ea_key == 2)
        {
            return 0;
        }
        else if (ea_key == 3)
        {
            alarms[count].Tone = (alarms[count].Tone + 1) % 3;
        }
        else if (ea_key == 4)
        {
            alarms[count].Tone = (alarms[count].Tone - 1 + 3) % 3;
        }
    }

    LCD_Clear();
    LCD_SetCursor(0, 2);
    LCD_String("REPEAT STATE");
    LCD_SetCursor(1, 2);
    LCD_String(repeat_state[alarms[count].Repeat_state]);

    while (1)
    {
        LCD_SetCursor(1, 2);
        LCD_String(repeat_state[alarms[count].Repeat_state]);
        _delay_ms(100);
        LCD_SetCursor(1, 2);
        LCD_String("               ");
        _delay_ms(100);

        ea_key = Key_Pressed();

        if (ea_key == 1)
        {
            break;
        }
        else if (ea_key == 2)
        {
            return 0;
        }
        else if (ea_key == 3)
        {
            alarms[count].Repeat_state = (alarms[count].Repeat_state + 1) % 3;
        }
        else if (ea_key == 4)
        {
            alarms[count].Repeat_state = (alarms[count].Repeat_state - 1 + 3) % 3;
        }
    }

    alarms[count].Alarm_state = 1;
    rtc_t a_rtc;
    RTC_Get_Time(&a_rtc);
    alarms[count].Date[0] = a_rtc.date;
    alarms[count].Date[1] = a_rtc.month;
    alarms[count].Date[2] = a_rtc.year;

    return 1;
}

/* This function is to dispaly a comfirmation message during 
the idea of aborting the alarm functionality */
int A_Abort()
{
    LCD_Clear();
    LCD_SetCursor(0, 3);
    LCD_String("PROCEED ");
    LCD_SetCursor(1, 0);
    LCD_String("WITHOUT SAVE?");
    int abort_key = 0;
    while (1)
    {
        abort_key = Key_Pressed();
        if (abort_key == 1)
        {
            LCD_Clear();
            return 1;
            
        }
        else if (abort_key == 2)
        {
            LCD_Clear();
            return 0;
        }
    }
}

/* Tracking whether any of the alarms is on */
int Alarm_State(){
    if (alarm_t>0){
        return 1;
    }
    return 0;
}

/* Handling the things once enter alarm setting */
void Alarm_setting(int *LEVEL, int *ITEM)
{
    int count = 0;
    int a_key;

    LCD_Clear();
    LCD_SetCursor(0, 2);
    LCD_String("ALARM SETTINGS");

    while (1)
    {
        // create alarm
        if (ITEM[1] == 0)
        {
            LCD_SetCursor(1, 2);
            LCD_String("CREATE ALARM");
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

            for (count = 0; count < 6; count++)
            {
                if (alarms[count].Alarm_state == 0)
                {
                    while(1){
                        if (Edit_Alarm(count))
                        {
                            alarm_t += 1;
                            LCD_Clear();
                            LCD_SetCursor(0, 1);
                            LCD_String("ALARM CREATED");
                            LCD_SetCursor(1, 1);
                            //LCD_Num(count);
                            LCD_String("SUCESSFULLY");
                            _delay_ms(1000);

                            A_Sort();
                            *LEVEL=2;
                            //ITEM[*LEVEL] = 0;
                            return; 
                        }
                        else if(A_Abort())
                        {
                            *LEVEL=2;
                            //ITEM[*LEVEL] = 0;
                            return;                        
                        }        
                    }
 
                }
            }

            if (count == 6)
            {
                LCD_Clear();
                LCD_SetCursor(0, 1);
                LCD_String("CAN'T CREATE");
                LCD_SetCursor(1, 5);
                LCD_String("ALARMS");
                _delay_ms(5000);

                ITEM[1] = 1;
            }

            *LEVEL = 2;
            return;
        }

        // Edit/Show alarm
        else if (ITEM[1] == 1)
        {
            LCD_SetCursor(1, 2);
            LCD_String("EDIT/DELETE");
            Key_handle(3, ITEM, LEVEL);

            if (*LEVEL == 2)
            {
                continue;
            }
            else if (*LEVEL == 1)
            {
                ITEM[2] = 0;
                return;
            }

            if (alarm_t == 0)
            {
                LCD_Clear();
                LCD_SetCursor(0, 1);
                LCD_String("NO ALARMS TO");
                LCD_SetCursor(1, 5);
                LCD_String("EDIT");
                _delay_ms(2000);

                LCD_Clear();
                LCD_SetCursor(0, 1);
                LCD_String("NEW ALARM");
                LCD_SetCursor(1, 5);
                LCD_String("CREATION");
                _delay_ms(3000);

                ITEM[1] = 0;
                continue;
            }

            // continue with edit alarm
            count = 0;
            while (alarms[count].Alarm_state == 0)
            {
                count = (count + 1) % 6;
            }

            LCD_Clear();
            while (1)
            {

                LCD_SetCursor(0, 1);
                LCD_String("SELECT ALARM");
                LCD_SetCursor(1, 0);
                LCD_String("ALARM :");
                LCD_Num(count + 1);

                a_key = Key_Pressed();

                if (a_key == 1)
                {
                    *LEVEL += 1;
                    LCD_Clear();
                    while (1)
                    {

                        LCD_SetCursor(0, 1);
                        LCD_String("ALARM :");
                        LCD_Num(count + 1);
                        if (ITEM[3] == 0)
                        {
                            LCD_SetCursor(1, 3);
                            LCD_String("EDIT ");

                            Key_handle(2, ITEM, LEVEL);

                            if (*LEVEL == 4)
                            {
                                continue;
                            }
                            else if (*LEVEL == 3)
                            {
                                break;
                            }

                            Edit_Alarm(count);
                            A_Sort();
                            LCD_Clear();
                            *LEVEL = 3;
                            break;
                        }
                        else if (ITEM[3] == 1)
                        {
                            LCD_SetCursor(1, 3);
                            LCD_String("DELETE");
                            Key_handle(2, ITEM, LEVEL);

                            if (*LEVEL == 4)
                            {
                                continue;
                            }
                            else if (*LEVEL == 3)
                            {
                                break;
                            }

                            LCD_Clear();
                            LCD_SetCursor(0, 1);
                            LCD_String("PROCEED WITH");
                            LCD_SetCursor(1, 3);
                            LCD_String("DELETE?");
                            //_delay_ms(2000);

                            while (1)
                            {
                                a_key = Key_Pressed();
                                if (a_key == 1)
                                {
                                    Delete_Alarm(count);
                                    LCD_Clear();
                                    LCD_SetCursor(0, 1);
                                    LCD_String("SUCESSFULLY");
                                    LCD_SetCursor(1, 3);
                                    LCD_String("DELETED");
                                    _delay_ms(2000);
                                    LCD_Clear();
                                    *LEVEL = 2;
                                    ITEM[1] = 0;
                                    return;
                                    //break;
                                }
                                else if (a_key == 2)
                                {
                                    LCD_Clear();
                                    *LEVEL = 2;
                                    break;
                                }

                                //continue;
                            }
                        }
                    }
                }
                else if (a_key == 2)
                {
                    LCD_Clear();
                    *LEVEL -= 1;
                    break;
                }
                else if (a_key == 3)
                {
                    while (alarms[count].Alarm_state == 0)
                    {
                        count = (count + 1) % 6;
                    }
                    continue;
                }
                else if (a_key == 4)
                {
                    while (alarms[count].Alarm_state == 0)
                    {
                        count = (count - 1 + 6) % 6;
                    }
                    continue;
                }
            }

            LCD_Clear();
            return;
        }

        else if (ITEM[1] == 2)
        {
            LCD_SetCursor(1, 2);
            LCD_String("DELETE ALL");
            Key_handle(3, ITEM, LEVEL);

            if (*LEVEL == 2)
            {
                continue;
            }
            else if (*LEVEL == 1)
            {
                ITEM[*LEVEL] = 0;
                return;
            }

            LCD_Clear();
            LCD_SetCursor(0, 1);
            LCD_String("PROCEED WITH");
            LCD_SetCursor(1, 3);
            LCD_String("DELETE?");
            //_delay_ms(2000);

            while (1)
            {
                a_key = Key_Pressed();
                if (a_key == 1)
                {
                    for (count = 0; count < 6; count++)
                    {
                        if (alarms[count].Alarm_state)
                        {
                            Delete_Alarm(count);
                        }
                    }
                    alarm_t = 0;

                    LCD_Clear();
                    LCD_SetCursor(0, 1);
                    LCD_String("SUCESSFULLY");
                    LCD_SetCursor(1, 3);
                    LCD_String("DELETED");
                    _delay_ms(2000);
                    LCD_Clear();

                    //check
                    ITEM[1] = 0;
                    *LEVEL = 2;
                    return;
                }
                //check

                else if (a_key == 2)
                {
                    *LEVEL -= 1;
                    break;
                }
                continue;
            }

            LCD_Clear();
            *LEVEL = 2;
            return;
        }
    }
}

/* Things happening during an alarm time */
void Alarm_Time_Functionality()
{ // check the alarm time with current time for activate the alarm
    int s_value;
    int position = alarms[ha_count].Tone;
    LCD_Clear();
    LCD_SetCursor(0, 3);
    LCD_String(" ALARM :");
    LCD_Num(ha_count + 1);
    LCD_SetCursor(1, 2);
    LCD_String(alarm_names[alarms[ha_count].Name]);

    if (position == 0)
    {
        s_value = ring_alarm(melody1);
    }
    else if (position == 1)
    {
        s_value = ring_alarm(melody2);
    }
    else if (position == 2)
    {
        s_value = ring_alarm(melody3);
    }
    //				else if(position==3){key=ring_alarm(melody4);}
    // 				else {key=ring_alarm(melody5);}

    if (s_value == 1)
    {
        // repeat mode analyzing
        Repeat_Handle(ha_count);
    }
    else
    {
        // snooze analyzing
        if (alarms[ha_count].A_Time[1] < (60 - snooze_time))
        {
            alarms[ha_count].A_Time[1] = alarms[ha_count].A_Time[1] + snooze_time;
        }
        else
        {
            alarms[ha_count].A_Time[1] = (alarms[ha_count].A_Time[1]) % snooze_time;
            alarms[ha_count].A_Time[0]+=1;
        }
    }
    A_Sort();
    LCD_Clear();
}