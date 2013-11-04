/*
 * TWI_lbr.c
 *
 * Created: 2013-11-04 15:53:52
 *  Author: Marek
 */ 

#ifndef _TWI_LBR_C_
#define _TWI_LBR_C_
#include "TWI_lbr.h"

void I2C_Init(uint8_t BitRate, uint8_t prescaler)
{
	TWBR = BitRate;
	TWSR = prescaler;
}

void I2C_START(void)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
}

void I2C_STOP(void)
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
	while(!(TWCR & _BV(TWSTO)));
}

void I2C_SendByte(uint8_t bajt)
{
	TWDR = bajt;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
}

uint8_t I2C_ReadByte(uint8_t ack)
{
	TWCR = _BV(TWINT) | (ack << TWEA) | _BV(TWEN);
	while(!(TWCR & _BV(TWINT)));
	return TWDR;
}

void I2C_SendBuf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf)
{
	I2C_START();
	I2C_SendByte(sla);
	I2C_SendByte(adr);
	while (len--) I2C_SendByte(*buf++);
	I2C_STOP();
}

void I2C_ReadBuf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf)
{
	I2C_START();
	I2C_SendByte(sla);
	I2C_SendByte(adr);
	I2C_START();
	I2C_SendByte(sla+1);
	while (len--) *buf++ = I2C_ReadByte(len ? ACK:NACK);
	I2C_STOP();
}


#endif	/*  _TWI_LBR_C_ */