/*
 * LCD_wysw_lbr.h
 *
 * Created: 2013-06-11 23:34:35
 *  Author: Marek
 */ 


#ifndef LCD_WYSW_LBR_H_
#define LCD_WYSW_LBR_H_

#include "HD44780.h"
#include "LCD_wysw_lbr.h"


void LCD_WriteHex(uint8_t num);
void LCD_WriteHexShort(uint8_t num);
void LCD_WriteDec8(uint8_t num);
void LCD_WriteDec16(uint16_t num);


#endif /* LCD_WYSW_LBR_H_ */