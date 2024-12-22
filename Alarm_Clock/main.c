/*
 * Alarm_Clock.c
 *
 * Created: 12/11/2024 6:29:06 PM
 * Author : PHAN ANH VU
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "LCD_4.h"
#include "I2C_Master.h"
#include "Keypad.h"
#include "DS1307.h"
#include "Buzzer.h"

int second,minute,hour,day,date,month,year;
int alarm_hour = -1;
int alarm_minute = -1;
bool alarm_set = false;
char temp_buf[5];

void init_Display()
{
	LCD_Init();
	LCD_String_xy(1, 10, "-");
	if(alarm_set == false)
	{
		LCD_String_xy(1, 13, "OFF");
	}
	else
	{
		LCD_String_xy(1, 13, "ON ");
	}
}

void setAlarm() {
	char buffer[20]={0};
	char key[2] = {0};
	int temp_hour = 0, temp_minute = 0;
	LCD_Clear();
	LCD_String_xy(0, 0, "Set alarm");
	LCD_String_xy(1, 0, "HH:MM");
	LCD_Set_Cursor(1, 8);
	

	// Enter hour
	for (int i = 0; i < 2; i++) {
		key[i] = keyfind();
		if (key[i] >= '0' && key[i] <= '9') {
			temp_hour = temp_hour * 10 + (key[i] - '0');
			LCD_Char(key[i]);
		}
	}
	
	if (temp_hour > 23){
		LCD_Clear();
		LCD_String_xy(0, 1, "Wrong hour !!!");
		LCD_String_xy(1, 3, "Reset alarm");
		_delay_ms(2000);
		setAlarm();
		return;
	}

	// Display ':'
	LCD_Char(':');
	
	
	// Enter minute
	for (int i = 0; i < 2; i++) {
		key[i] = keyfind();
		if (key[i] >= '0' && key[i] <= '9') {
			temp_minute = temp_minute * 10 + (key[i] - '0');
			LCD_Char(key[i]);
		}
	}
	
	if (temp_minute > 59){
		LCD_Clear();
		LCD_String_xy(0, 0, "Wrong minute !!!");
		LCD_String_xy(1, 2, "Reset alarm");
		_delay_ms(2000);
		setAlarm();
		return;
	}

	// Update alarm time
	alarm_hour = temp_hour;
	alarm_minute = temp_minute;
	alarm_set = true;

	// Display notify set success
	LCD_Clear();
	LCD_String_xy(0, 3, "Alarm Set");
	sprintf(buffer, "%02d:%02d", alarm_hour, alarm_minute);
	LCD_String_xy(1, 5, buffer);
	_delay_ms(2000);
	LCD_Clear();
	init_Display();
}



void display_alarm_time()
{
	char buffer[20];
	
	LCD_Clear();
	
	if (alarm_set == true)
	{
		LCD_String_xy(0, 3, "Alarm Set");
	}
	else
	{
		LCD_String_xy(0, 3, "Alarm Reset");
	}
	sprintf(buffer, "%02d:%02d", alarm_hour, alarm_minute);
	LCD_String_xy(1, 4, buffer);
	_delay_ms(2000);
	LCD_Clear();
	init_Display();
}

// Check condition alarm
void checkAlarm() {
	hour = (hour & 0b00111111);
	int hour_dec = ((hour >> 4) * 10) + (hour & 0x0F);
	int minute_dec = ((minute >> 4) * 10) + (minute & 0x0F);
	if (alarm_set && (hour_dec == alarm_hour) && (minute_dec == alarm_minute)) {
		sprintf(temp_buf, "%02d:%02d", alarm_hour, alarm_minute);
		// Turn on alarm (e.g. turn on LED or speaker)
		LCD_Clear();
		LCD_String_xy(0, 0, "ALARM Ringing!!!");
		LCD_String_xy(1, 4, temp_buf);
		
		InitMusic();       //Init music for buzzer
		AlarmSound();
		ExitMusic();
		
		alarm_set = false;						// Reset alarm flag
		alarm_hour = -1;						// Reset alarm hour
		alarm_minute = -1;						// Reset alarm minute
		LCD_Clear();
		init_Display();
	}
}



ISR(INT2_vect) {
	LCD_Clear();
	LCD_String_xy(0,0, "1:Set");
	LCD_String_xy(1,0, "2:Reset");
	LCD_String_xy(0,10, "3:Read");
	LCD_String_xy(1,10, "O:Exit");
	char c = keyfind();
	
	switch(c){
		case ('1'):
		{
			setAlarm();
			break;
		}
		case ('2'):
		{
			alarm_hour = -1;
			alarm_minute = -1;
			alarm_set = false;
			display_alarm_time();
			break;
		}
		case ('3'):
		{
			display_alarm_time();
			break;
		}
		default:
		{
			LCD_Clear();
			init_Display();
			break;
		}
	}
	
}

const char *days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
	
int main(void)
{
	char buffer[13] = {0};
	
	I2C_Init();
	
	//LCD_TurnOn();
	LCD_Init();
	_delay_ms(2);
	init_Display();

	//Set clock for DS1307: run in one time
	//RTC_Set_Clock(21, 16, 00);  
	//RTC_Set_Calendar(3, 17, 12, 24); 

	//Set interrupt when push button in PB2
	PORTB |= (1<<2);					//PB2 = input pull-up
	GICR |= (1<<INT2);					//enable INT2
	MCUCSR &= ~(1<<ISC2);				//falling edge
	sei();								//enable global interrupt
	
	
	while (1)
	{
		RTC_Read_Calendar(3, &day, &date, &month, &year);	// Read calendar with day address i.e location is 3
		sprintf(buffer, "%02x/%02x/20%02x %3s", date, month, year, days[day-1]);
		LCD_String_xy(0,0,buffer);
		memset(buffer, 0, sizeof(buffer));
		_delay_ms(2);
		
		RTC_Read_Clock(0, &second, &minute, &hour);	/* Read clock with second add. i.e location is 0 */
		sprintf(buffer, "%02x:%02x:%02x", (hour & 0b00111111), minute, second);
		LCD_String_xy(1,0,buffer);
		memset(buffer, 0, sizeof(buffer));
		
		checkAlarm();
	}
}
