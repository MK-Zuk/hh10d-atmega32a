/*
 * LCD_wysw_lbr.c
 *
 * Created: 2013-06-11 23:36:01
 *  Author: Marek
 */ 


#include "LCD_wysw_lbr.h"

void LCD_WriteHex(uint8_t num)
{
	uint8_t hi, lo;
	hi=num & 0xF0;
	hi=hi >>4;
	lo=num & 0x0F;
	LCD_WriteData('0');
	LCD_WriteData('x');
	if(hi<10)
	{LCD_WriteData(hi+'0');
	}else LCD_WriteData(hi-10+'A');
	if(lo<10)
	{LCD_WriteData(lo+'0');
	}else LCD_WriteData(lo-10+'A');
}

void LCD_WriteHexShort(uint8_t num)
{
	uint8_t hi, lo;
	hi=num & 0xF0;
	hi=hi >>4;
	lo=num & 0x0F;
	LCD_WriteData('x');
	if(hi<10)
	{LCD_WriteData(hi+'0');
	}else LCD_WriteData(hi-10+'A');
	if(lo<10)
	{LCD_WriteData(lo+'0');
	}else LCD_WriteData(lo-10+'A');
}

void LCD_WriteDec8(uint8_t num)
{
	uint8_t sto,dzies,jedn;
	jedn = num % 10;
	num = num/10;
	dzies = num%10;
	sto = num/10;
	LCD_WriteData(sto+'0');
	LCD_WriteData(dzies+'0');
	LCD_WriteData(jedn+'0');
}

void LCD_WriteDec16(uint16_t num)
{
	uint16_t temp[5];
	uint8_t i;
	for (i=0; i<5;i++)
	{
		temp[i] = num % 10;
		num = num/10;
	}
	
	for (i=0; i<5;i++)
	{
		LCD_WriteData(temp[4-i]+'0');
	}
}