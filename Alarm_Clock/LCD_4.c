#include "LCD_4.h"


void LCD_Init(void)
{
	LCD_Command_Dir |= 0xE0;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir |= 0xF0;			/* Make LCD data port direction as o/p */
	_delay_ms(20);		/* LCD Power ON delay always >15ms */
	LCD_Command_Port &= ~(1<<RW);  /*Make LCD in write mode*/
	LCD_Command(0x33);
	LCD_Command(0x32);	/* Send for 4 bit initialization of LCD  */
	LCD_Command(0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	LCD_Command(0x0C);	/* Display on cursor off */
	LCD_Command(0x06);	/* Increment cursor (shift cursor to right) */
	LCD_Command(0x01);	/* Clear display screen */
	_delay_ms(4);
	LCD_Command(0x80);  /* Cursor at home position */
}


void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port = (LCD_Data_Port & 0x0F) | (cmnd & 0xF0);/* Sending upper nibble */
	LCD_Command_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Command_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(5);
	LCD_Command_Port &= ~ (1<<EN);
	
	_delay_us(200);
	
	LCD_Data_Port = (LCD_Data_Port & 0x0F) | (cmnd << 4);/* Sending lower nibble */
	LCD_Command_Port |= (1<<EN);
	_delay_us(5);
	LCD_Command_Port &= ~ (1<<EN);
	
	_delay_ms(2);
	
}

void LCD_Char(unsigned char data){
	LCD_Data_Port = (LCD_Data_Port & 0x0F) | (data & 0xF0);/* Sending upper nibble */
	LCD_Command_Port |= (1<<RS);  /* RS=1, data reg. */
	LCD_Command_Port|= (1<<EN);
	_delay_us(5);
	LCD_Command_Port &= ~ (1<<EN);
	
	_delay_us(200);
	
	LCD_Data_Port = (LCD_Data_Port & 0x0F) | (data << 4);  /* Sending lower nibble */
	LCD_Command_Port |= (1<<EN);
	_delay_us(5);
	LCD_Command_Port &= ~ (1<<EN);
	
	_delay_ms(2);
}

void LCD_String(char *str){
	for (int i = 0; str[i] != 0; i++)
	{
		LCD_Char(str[i]);
	}
}

void LCD_String_xy(char row, char pos, char* str)
{
	if (row == 0 && pos < 16)
	LCD_Command((pos & 0x0f) | 0x80);
	else if (row == 1 && pos < 16)
	LCD_Command((pos & 0x0f) | 0xC0);
	LCD_String(str);
}

void LCD_Set_Cursor(char row, char pos)
{
	if (row == 0 && pos < 16)
	LCD_Command((pos & 0x0f) | 0x80);
	else if (row == 1 && pos < 16)
	LCD_Command((pos & 0x0f) | 0xC0);
}

void LCD_Clear()
{
	LCD_Command (0x01);		/* Clear display */
	_delay_ms(2);
	LCD_Command (0x80);		/* Cursor at home position */
	_delay_ms(50);
}

