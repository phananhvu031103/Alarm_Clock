#ifndef __LCD_4_h__
#define __LCD_4_h__

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define LCD_Data_Dir DDRC		/* Define LCD data port direction */
#define LCD_Command_Dir DDRD	/* Define LCD command port direction register */
#define LCD_Data_Port PORTC		/* Define LCD data port */
#define LCD_Command_Port PORTD	/* Define LCD data port */

#define RW 5
#define RS 6			/*Define Register Select (data/command reg.)pin*/
#define EN 7			/*Define Enable signal pin*/

void LCD_Init(void);
void LCD_Command(unsigned char command);
void LCD_Char(unsigned char data);
void LCD_String(char *str);
void LCD_String_xy(char row, char pos, char* str);
void LCD_Clear(void);
void LCD_Set_Cursor(char row, char pos);

#endif
