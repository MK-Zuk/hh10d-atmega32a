/*
 * TWI_lbr.h
 *
 * Created: 2013-11-04 15:55:55
 *  Author: Marek
 */ 


#ifndef TWI_LBR_H_
#define TWI_LBR_H_
#include <avr/io.h>

// I2C (TWI) Library
#define ACK 1
#define NACK 0

#define PRESC_1		0x00
#define PRESC_4		0x01
#define PRESC_16	0x02
#define PRESC_64	0x03

void I2C_Init(uint8_t BitRate, uint8_t prescaler);
void I2C_START(void);
void I2C_STOP(void);
void I2C_SendByte(uint8_t bajt);
uint8_t I2C_ReadByte(uint8_t ack);
void I2C_SendBuf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf);
void I2C_ReadBuf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf);



#endif /* TWI_LBR_H_ */