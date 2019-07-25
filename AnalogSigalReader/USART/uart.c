/*
* uart.c
*
* Created: 16.07.2019 13:55:48
*  Author: Dominika Wójcik
*/

#include "uart.h"
#include "avr/io.h"
#include <stdlib.h>
#include <util/delay.h>


void usart_put_float(float num, int precission)
{
	char c[10];
	int inum = num;
	int numSize = sizeof(inum) + precission;
	dtostrf(num, numSize, precission, c);
	uart_puts(c);
}

void usart_put_int(int num)
{
	char c[6];
	itoa(num, c,10);
	usart_put_string(c);
}

void usart_put_string(char *str)
{
	while(*str){
		usart_put_char(*str++);
	}
}


void usart_put_char(char data)
{
	/* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));
	_delay_ms(10);
	UDR0 = data;
}



void usart_init_transmission(unsigned int ubrr)
{
	/*Set baud rate */
	//UBRR0H = (unsigned char)(ubrr>>8);
	//UBRR0L = (unsigned char)ubrr;
	
	UBRR0 = ubrr;

	UCSR0B = (1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}
