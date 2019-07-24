/*
* uart.h
*
* Created: 16.07.2019 13:55:32
*  Author: Dominika Wójcik
*/


#ifndef UART_H_
#define UART_H_

#define UART_BAUD 9600
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)

#include <avr/io.h>

void usart_init_transmission(unsigned int);
void usart_put_char(char data);
void usart_put_string(char *str);
void usart_put_int(int num);
void usart_put_float(float num, int precission);

#endif /* UART_H_ */