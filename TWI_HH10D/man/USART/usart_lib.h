/*
 * usart_lib.h
 *
 * Created: 2013-11-08 23:20:19
 *  Author: Marek
 */ 


#ifndef USART_LIB_H_
#define USART_LIB_H_

#include <avr/interrupt.h>

#define BAUD_8MHZ_9600 51	//err 0,2
#define BAUD_8MHZ_19200 25	//err 0,2
#define BAUD_8MHZ_38400 12	//err 0,2

#define BUFFER_SIZE	6
#define SEND		0
#define RECEIVE		1

volatile uint8_t USART_flag;

void USART_init(uint16_t baud);
void USART_initInt(uint16_t baud);
void USART_softsend(uint8_t data);
void USART_sendInt(uint8_t *buff);
uint8_t USART_softread(void);
uint8_t USART_readInt(void);

void USART_WriteHex(uint8_t num);
void USART_WriteHexShort(uint8_t num);
void USART_WriteDec8(uint8_t num);
void USART_WriteDec8Short(uint8_t num);
void USART_WriteDec16(uint16_t num);

void USART_WriteStr(char *string, uint8_t lenght);
void USART_WriteStrShort(char *string);

#endif /* USART_LIB_H_ */