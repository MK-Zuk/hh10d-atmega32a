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
#include "USART/usart_lib.h"

#define ADRES	0xA2
#define TIMER1_START_VALUE	34286	//ustala punkt statrowy dla rejestru timer1 na czas 1s

enum bytes  {lo,hi};

union uint16_tim
{
	uint8_t bytes[2];
	uint16_t word;
};


volatile union uint16_tim timerdata;

void TIMER1_Init(void);

int main(void)
{
    uint8_t bufor[4];
	uint8_t conf[4];
	
	timerdata.bytes[lo] = 0;
	timerdata.bytes[hi] =0;
	
	DDRB = 0xFF;
	
	USART_initInt(BAUD_8MHZ_9600);
	_delay_ms(400);
	
	I2C_Init(24,PRESC_4);
	
	I2C_ReadBuf(ADRES,10,4,conf);
	
	TIMER1_Init();
	sei();
		
	while(1)
    {
        //TODO:: Please write your application code 
		
		if(USART_flag & _BV(RECEIVE))
		{
			if(USART_readInt() == 'a')
			{
				bufor[0]=timerdata.bytes[hi];
				bufor[1]=timerdata.bytes[lo];
				bufor[2]=timerdata.bytes[hi];
				bufor[3]=timerdata.bytes[lo];
				USART_sendInt(bufor);
			}
			if(USART_readInt() == 'c')
			{
				USART_sendInt(conf);
			}	
		}
    }
}


void TIMER1_Init(void)
{
	TCCR1B |= _BV(ICNC1);	//noise canceler
	TCCR1B |= _BV(ICES1);	//zbocze narastajace
	TCCR1B |= _BV(CS11);// | _BV(CS11);// | _BV(CS12);	//preskaler 8
							//zliczanie normalne w gore
	TCNT1 = TIMER1_START_VALUE;
	TIMSK|= _BV(TOIE1);		//przerwanie na przepelnienie
	TIMSK |= _BV(TICIE1);		//przerwanie na zewnetrzny sygnal
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = TIMER1_START_VALUE;
	//timerdata.bytes[lo]=ICR1L;
	//timerdata.bytes[hi]=ICR1H;
	//ICR1L = 0;
	//ICR1H = 0;
	PORTB ^= _BV(6);
}

ISR(TIMER1_CAPT_vect)
{
	static uint8_t timericr;
	static uint16_t timerold;
	timericr = ICR1;
	if(timericr>timerold)
	{
		timerdata.word = timericr;
	}
	timerold = timericr;
	
}
