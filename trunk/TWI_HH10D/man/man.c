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
	uint8_t i;
	timerdata.bytes[lo] = 0;
	timerdata.bytes[hi] =0;
	
	DDRB = 0xFF;
	
	LCD_Initalize();
	LCD_Home();
	LCD_WriteData('s');
	_delay_ms(400);
	
	I2C_Init(24,PRESC_4);
	
	I2C_ReadBuf(ADRES,10,4,bufor);
	LCD_Home();
	
	for(i=0;i<4;i++) LCD_WriteHexShort(bufor[i]);
	
	TIMER1_Init();
	sei();
		
	while(1)
    {
        //TODO:: Please write your application code 
		LCD_GoTo(0,1);
		LCD_WriteHexShort(timerdata.bytes[hi]);
		LCD_WriteHexShort(timerdata.bytes[lo]);
		_delay_ms(1000);
    }
}


void TIMER1_Init(void)
{
	TCCR1B |= _BV(ICNC1);	//noise canceler
	TCCR1B |= _BV(ICES1);	//zbocze narastajace
	TCCR1B |= _BV(CS12);// | _BV(CS11);// | _BV(CS12);	//preskaler 256
							//zliczanie normalne w gore
	TCNT1 = TIMER1_START_VALUE;
	TIMSK|= _BV(TOIE1);		//przerwanie na przepelnienie
}

ISR(TIMER1_OVF_vect)
{
	TCNT1 = TIMER1_START_VALUE;
	timerdata.word = ICR1;
	ICR1 = 0;
	PORTB ^= _BV(6);
}


