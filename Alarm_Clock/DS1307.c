#include "DS1307.h"

bool IsItPM(char hour_)
{
	if(hour_ & (AMPM))
	return 1;
	else
	return 0;
}

void RTC_Read_Clock(char read_clock_address, int *second, int *minute, int *hour)
{
	I2C_Start(Device_Write_address);/* Start I2C communication with RTC */
	I2C_Write(read_clock_address);	/* Write address to read */
	I2C_Repeated_Start(Device_Read_address);/* Repeated start with device read address */

	*second = I2C_Read_Ack();	/* Read second */
	*minute = I2C_Read_Ack();	/* Read minute */
	*hour = I2C_Read_Nack();		/* Read hour with Nack */
	I2C_Stop();			/* Stop i2C communication */
}

void RTC_Read_Calendar(char read_calendar_address, int *day, int *date, int *month, int *year)
{
	I2C_Start(Device_Write_address);
	I2C_Write(read_calendar_address);
	I2C_Repeated_Start(Device_Read_address);

	*day = I2C_Read_Ack();			/* Read day */
	*date = I2C_Read_Ack();			/* Read date */
	*month = I2C_Read_Ack();		/* Read month */
	*year = I2C_Read_Nack();		/* Read the year with N_ack */
	I2C_Stop();						/* Stop i2C communication */
}

void RTC_Set_Clock(uint8_t hour, uint8_t minute, uint8_t second) {
	second = (second / 10 * 16) + (second % 10);  // Convert second to BCD
	minute = (minute / 10 * 16) + (minute % 10);  // Convert minute to BCD
	hour = (hour / 10 * 16) + (hour % 10);        // Convert hour to BCD

	I2C_Start(Device_Write_address);      /* Start I2C communication with RTC */
	I2C_Write(0x00);       // Second register address
	I2C_Write(second);     
	I2C_Write(minute);     
	I2C_Write(hour);      
	I2C_Stop();            /* Stop i2C communication */
}

void RTC_Set_Calendar(uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
	day		= (day  /  10 * 16)  |  (day % 10);           // Convert day to BCD
	date	= (date /  10 * 16)  |  (date % 10);        // Convert date to BCD
	month	= (month / 10 * 16)  |  (month % 10);       // Convert month to BCD
	year	= (year /  10 * 16)  |  (year % 10);        //Convert year to BCD

	I2C_Start(Device_Write_address);    /* Start I2C communication with RTC */  
	I2C_Write(0x03);        // Day register address
	I2C_Write(day);        
	I2C_Write(date);       
	I2C_Write(month);      
	I2C_Write(year);       
	I2C_Stop();            /* Stop i2C communication */
}
