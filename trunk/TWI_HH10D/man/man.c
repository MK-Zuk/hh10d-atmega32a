/*
 * man.c
 *
 * Created: 2013-11-04 15:19:40
 *  Author: Marek
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LCD/LCD_wysw_lbr.h"
#include "LCD/HD44780.h"
#include "TWI/TWI_lbr.h"


#define ADRES	0xA2




int main(void)
{
    uint8_t bufor[4];
	uint8_t i;
	
	LCD_Initalize();
	LCD_Home();
	LCD_WriteData('s');
	_delay_ms(400);
	
	I2C_Init(24,PRESC_4);
	
	I2C_ReadBuf(ADRES,10,4,bufor);
	LCD_Home();
	
	for(i=0;i<4;i++) LCD_WriteHexShort(bufor[i]);
		
	while(1)
    {
        //TODO:: Please write your application code 
    }
}


