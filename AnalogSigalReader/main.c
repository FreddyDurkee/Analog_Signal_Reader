/*
* AnalogSigalReader.c
*
* Created: 22.07.2019 13:25:32
* Author : Dominika Wójcik
*/

#define  NUM_AVG_SAMPLES 10
#define  DEF_SAMPLES NUM_AVG_SAMPLES*CHANNELS_AMOUNT
#define  CHANNELS_AMOUNT 2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "UART_LIB/uart.h"
#include "USART/uart.h"
#include "ADC/adc.h"


volatile uint16_t adc1_result = 0;
volatile uint16_t adc0_result = 0;
volatile uint16_t adc1_sum = 0, sum1;
volatile uint16_t adc0_sum = 0, sum0;
volatile uint8_t counter = 0;
volatile uint8_t channel = 0;
volatile uint8_t flag = 0;

float convert_to_voltage(uint16_t);
void usart_putf(float num, int precission);
void milis_timer(uint8_t miliS);

int main(void)
{
	adc_init_triggered_conversions(DF_128, timer0_compare_match, REF_11);
	set_channel(channel);
	uart_init(__UBRR);
	milis_timer(4);
	
	sei();
	
	//start_conversion();
	float voltage;
	float average;
	uint16_t i = 0 ;
	char adc_str[6], i_str[6];
	while (1)
	{
		if(counter == 0){
			average = sum0 * 1.0/NUM_AVG_SAMPLES;
			voltage = convert_to_voltage(average);
			usart_putf(voltage, 3);
			uart_putc(';');
			
			average = sum1 * 1.0/NUM_AVG_SAMPLES;
			voltage = convert_to_voltage(average);
			usart_putf(voltage, 3);
			uart_putc('\n');
		}
	}
}

ISR(TIMER0_COMPA_vect){	
}

ISR(ADC_vect){
	if(flag){
		adc1_result = ADCW;
		adc1_sum += adc1_result;
		ADMUX = 0b11000000;
		flag=0;
	}
	else{
		adc0_result = ADCW;
		adc0_sum += adc0_result;
		ADMUX = 0b11000001;
		flag=1;
	}
	counter++;
	if(counter >= DEF_SAMPLES){
		counter=0;
		sum1 = adc1_sum;
		sum0 = adc0_sum;
		adc0_sum = 0;
		adc1_sum = 0;
		
	}
}

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

void milis_timer(uint8_t miliS){
	TCCR0A |= (1<< WGM01);           // set CTC
	TCCR0B |= (1<<CS02) | (1<<CS00); //PRESCALER 1024
	OCR0A = miliS*7.8125-1; 		 // Fcpu*milis/(1000*2*N)-1
	TIMSK0 |= (1<<OCIE0A);
}