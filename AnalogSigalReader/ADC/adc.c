/*
* adc.c
*
* Created: 22.07.2019 13:26:06
*  Author: Dominika Wójcik
*/


#include "adc.h"


void set_prescaler(enum Division_Factor df){
	ADCSRA |= df;
}

void set_internal_reference(){
	ADMUX |= REF_11;
}

void set_channel(uint8_t channel){
	ADMUX |= (ADMUX & CLEAN_CHANNEL) | channel;
}

void turn_on_ADC(){
	ADCSRA |= (1<<ADEN);
}

void start_conversion(){
	ADCSRA |= (1<<ADSC);
}

void adc_init_triggered_conversions(enum Division_Factor df,enum  Trigger_Source ts,enum  Voltage_Reference vref){
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADATE);
	ADCSRA |= df;
	ADCSRB |= (ADCSRB & CLEAN_TRIGGER_SOURCE) | ts;
	ADMUX |= (ADMUX & CLEAN_TRIGGER_SOURCE) | vref;
}

void adc_init_single_conversion(enum Division_Factor df,enum  Voltage_Reference vref){
	ADCSRA |= (1<<ADEN);
	ADCSRA |= df;
	ADMUX |= (ADMUX & CLEAN_TRIGGER_SOURCE) | vref;
}


