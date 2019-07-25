/*
* AnalogSigalReader.c
*
* Created: 22.07.2019 13:25:32
* Author : Dominika Wójcik
*/

//#define F_CPU 16000000UL
//#define UART_BAUD 9600
//#define _UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)
#define  SAMPLES 10

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UART_LIB/uart.h"
#include "USART/uart.h"
#include "ADC/adc.h"


volatile uint16_t adc_result;
volatile uint16_t adc_sum = 0;
volatile uint8_t counter = 0;
volatile uint8_t channel = 0;
volatile uint8_t flag = 0;

float convert_to_voltage(uint16_t);
void usart_putf(float num, int precission);

int main(void)
{
	adc_init_single_conversion(DF_128, REF_11);
	set_channel(channel);
	uart_init(__UBRR);
	start_conversion();
	sei();
	
	float voltage;
	float average;
	
	while (1)
	{
		voltage = convert_to_voltage(adc_result);
		usart_putf(voltage, 3);
		uart_putc('\n');
		//if(counter==0){
			//average = adc_sum*1.0/SAMPLES;
			////voltage = convert_to_voltage(average);
			//usart_putf(average, 3);
			//adc_sum = 0;
			//if(flag == 0){
				//uart_putc(';');
			//}
			//else{
				//uart_putc('\n');
			//}	
		//}
	//}
}
}

ISR(ADC_vect){
	adc_result = ADCW;
	start_conversion();
	}
			
	//if(counter < SAMPLES){
		//adc_result = ADCW;
		//start_conversion();
		//adc_sum += adc_result;
		//counter++;
	//}
	//else{
		//counter = 0;
		//channel++;
		//channel %= 2;
		//set_channel(channel);
		//flag = channel;
	//}



float convert_to_voltage(uint16_t adc_result){
	return (adc_result * 1.1)/1024;
}

void usart_putf(float num, int precission)
{
	char c[10];
	int inum = num;
	int numSize = sizeof(inum) + precission;
	dtostrf(num, numSize, precission, c);
	uart_puts(c);
}