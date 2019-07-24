/*
 * AnalogSigalReader.c
 *
 * Created: 22.07.2019 13:25:32
 * Author : Dominika Wójcik
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ADC/adc.h"
#include "USART/uart.h"

volatile uint16_t adc_result;

float convert_to_voltage(uint16_t);

int main(void)
{
	adc_init_single_conversion(DF_128, REF_11);
	usart_init_transmission(__UBRR);
	
	set_channel(0);
	start_conversion();
    sei();
	
	float voltage;
	
    while (1) 
    {
		voltage = convert_to_voltage(adc_result);
		usart_put_float(voltage, 3);
		usart_put_string(" V\n");
    }
}

ISR(ADC_vect){
	adc_result = ADCW;
	start_conversion();
}

float convert_to_voltage(uint16_t adc_result){
	return (adc_result * 1.1)/1024;
}
