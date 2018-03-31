/*
 * main.c
 *
 * Created: 4/1/2018 2:04:40 AM
 * Author: mrsfdri
 */

// add header file
#include <io.h>
#include <mega8.h>
// delay
#include <delay.h>
// lcd
#include <alcd.h>
// convert bit to number
#include <stdlib.h>
#include <stdio.h>

// count bit
unsigned char bit_count = 0;
// feedback count bit return
unsigned char c = 0;
// temperature and humidity value
unsigned char i_rh, d_rh, i_temp, d_temp, check;
// buffer show result
unsigned char buff[16];
// loop count
unsigned char cl = 0;

//***** start methods *****//

void request(void)
{
	// DDRD.6 = 1;
	DDRD |= (1<<0);

	// PORTD.6 = 0;
	PORTD &= ~(1<<0);
	
	// delay_ms(18);
	delay_ms(18);
	
	// PORTD.6 = 1;
	PORTD |= (1<<0);
}



void response()
{	
	// PIND
	DDRD &= ~(1<<0);

	while(PIND & (1<<0))
	{
		delay_us(1);
		cl++;
		if (cl > 80) break;
	}

	cl = 0;
	while((PIND & (1<<0))==0)
	{	
		delay_us(40);
		cl++;
		if (cl > 2) break;
	}

	cl = 0;	
	while(PIND & (1<<0))
	{
		delay_us(40);
		cl++;
		if (cl > 2) break;
	}
}



unsigned char recive()
{
	while(bit_count<8)
	{
		bit_count++;

		while((PIND & (1<<0))==0);

		delay_us(30);

		if(PIND & (1<<0))
		{
			c=(c<<1)|(0x01);
		} else {
			c=c<<1;
		}
		while(PIND & (1<<0));
	}

	bit_count=0;

	return c;
}

void main(void)
{	
	unsigned char data[5];
	while (1)
		{
		

		}
}
