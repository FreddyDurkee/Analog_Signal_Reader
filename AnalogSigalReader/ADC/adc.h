/*
* adc.h
*
* Created: 22.07.2019 13:26:17
*  Author: Dominika Wójcik
*/


#ifndef ADC_H_
#define ADC_H_

#define CLEAN_CHANNEL 0b11111000
#define CLEAN_TRIGGER_SOURCE 0b11111000
#define CLEAN_VOLTAGE_REFERENCE 0b00111111

#include <avr/io.h>

enum Division_Factor { DF_2 = 1, DF_4 = 2, DF_8 = 3, DF_16 = 4, DF_32 = 5, DF_64 = 6, DF_128 = 7 };
enum Trigger_Source { free_running_mode = 0, Aanalog_comparator = 1, ext_interrupt_request = 2,
						timer0_compare_match = 3, timer0_overflow = 4, timer1_compare_match = 5,
						timer1_overflow = 6, timer1_capture_event = 7};

enum Voltage_Reference { REF_VCC = 0b01000000, REF_11 = 0b11000000};


void set_prescaler(enum Division_Factor df);

void set_internal_reference();

void set_channel(uint8_t channel);

void turn_on_ADC();

void start_conversion();

void adc_init_triggered_conversions(enum Division_Factor df,enum  Trigger_Source ts,enum  Voltage_Reference vref);

void adc_init_single_conversion(enum Division_Factor df,enum  Voltage_Reference vref);

#endif /* ADC_H_ */