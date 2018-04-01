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

	// Initial LCD
	lcd_init(16);
	

	lcd_clear();
	lcd_gotoxy(0, 0);
	lcd_puts("GeekTab.ir");
	delay_ms(1000);
	lcd_gotoxy(0, 1);
	lcd_puts("T: ");
	lcd_gotoxy(7, 1);
	lcd_puts("H: ");
	
	
	while (1)
	{
		request();
		response();

		i_rh   = recive();
		d_rh   = recive();
		i_temp = recive();
		d_temp = recive();
		check  = recive();

		if ((i_rh + d_rh + i_temp + d_temp) != check)
		{
			lcd_gotoxy(3, 1);
			lcd_puts("E");

			lcd_gotoxy(10, 1);
			lcd_puts("E");
		} else
		{
			itoa(i_rh, data);
			lcd_gotoxy(3, 1);
			lcd_puts(data);


			itoa(i_temp, data);
			lcd_gotoxy(10, 1);
			lcd_puts(data);
		}
		delay_ms(2000);
	}
}
