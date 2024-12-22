#ifndef __I2C_MASTER_h_
#define __I2C_MASTER_h_

#define F_CPU 8000000UL		/* Define CPU clock Frequency 8MHz */
#define SCL_CLK 100000UL
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include Delay header file */
#include <string.h>		/* Include string header file */

#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */

void I2C_Init();
uint8_t I2C_Start(char write_address);
uint8_t I2C_Repeated_Start(char read_address);
uint8_t I2C_Write(char data);
char I2C_Read_Ack();		
char I2C_Read_Nack();
void I2C_Stop();	

#endif