#ifndef __DS1307_H__
#define  __DS1307_H__


#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "I2C_Master.h"


#define Device_Write_address	0xD0  /* Define RTC DS1307 slave write address */
#define Device_Read_address		0xD1  /* Make LSB bit high of slave address for read */
#define TimeFormat12			0x40  /* Define 12 hour format 0100.0000*/
#define AMPM					0x20  /* 0010.0000 */

void RTC_Read_Clock(char read_clock_address, int *second, int *minute, int *hour);
void RTC_Read_Calendar(char read_calendar_address, int *day, int *date, int *month, int *year);
void RTC_Set_Clock(uint8_t hour, uint8_t minute, uint8_t second);
void RTC_Set_Calendar(uint8_t day, uint8_t date, uint8_t month, uint8_t year);

#endif