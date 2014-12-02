/*
 * inputs.c
 *
 * Created: 2014/11/22 07:30:45 PM
 *  Author: JanZwiegers
 */

#include <asf.h>
#include "uart.h"
#include "inputs.h"

#define INPUT_DEBOUNCE 20 // 1000 ms

static uint16_t input_timers[8];
static uint8_t input_status;

void inputs_init( void )
{
	uint8_t c;
	input_status = 0;
	for(c=0; c<8; c++) {
		input_timers[c] = 0;
	}
}

uint8_t inputs_get_value( void )
{
	uint8_t a = PINA & 0x0f;
	uint8_t d = PIND & 0x0c;
	uint8_t b = PINB & 0x03;
	uint8_t v = (a << 4) | (b) | (d);
	return v;
}

void inputs_service( uint8_t delay )
{
	uint8_t v = inputs_get_value();

	if((v & INPUT_CLOSE_BIT) == INPUT_CLOSE_BIT) {
		if(input_timers[INPUT_CLOSE] < INPUT_DEBOUNCE) {
			input_timers[INPUT_CLOSE] += delay;
		}
		else if(input_timers[INPUT_CLOSE] == INPUT_DEBOUNCE) {
			uart_write_string("CLOSE\r\n");
			input_status |=INPUT_CLOSE_BIT;
			input_timers[INPUT_CLOSE] += delay;
		}
	}
	else {
		input_timers[INPUT_CLOSE] = 0;
		//input_status &= ~INPUT_CLOSE_BIT;
	}

	if((v & INPUT_OPEN_BIT) == INPUT_OPEN_BIT) {
		if(input_timers[INPUT_OPEN] < INPUT_DEBOUNCE) {
			input_timers[INPUT_OPEN] += delay;
		}
		else if(input_timers[INPUT_OPEN] == INPUT_DEBOUNCE) {
			uart_write_string("OPEN\r\n");
			input_status |=INPUT_OPEN_BIT;
			input_timers[INPUT_OPEN] += delay;
		}
	}
	else {
		input_timers[INPUT_OPEN] = 0;
		//input_status &= ~INPUT_OPEN_BIT;
	}

	if((v & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		if(input_timers[INPUT_TRIGGER] < 1000) {
			input_timers[INPUT_TRIGGER] += delay;
		}
		else if(input_timers[INPUT_TRIGGER] == 1000) {
			uart_write_string("TRIGGER\r\n");
			input_status |= INPUT_TRIGGER_BIT;
			input_timers[INPUT_TRIGGER] += delay;
		}
	}
	else {
		input_timers[INPUT_TRIGGER] = 0;
		//input_status &= ~INPUT_TRIGGER_BIT;
	}

	if((v & INPUT_LIGHT_BIT) == INPUT_LIGHT_BIT) {
		if(input_timers[INPUT_LIGHT] < INPUT_DEBOUNCE) {
			input_timers[INPUT_LIGHT] += delay;
		}
		else if(input_timers[INPUT_LIGHT] == INPUT_DEBOUNCE) {
			uart_write_string("LIGHT\r\n");
			input_status |= INPUT_LIGHT_BIT;
			input_timers[INPUT_LIGHT] += delay;
		}
	}
	else {
		input_timers[INPUT_LIGHT] = 0;
		//input_status &= ~INPUT_LIGHT_BIT;
	}

}

uint8_t inputs_get_status( void )
{
	uint8_t in = input_status;
	input_status &= 0xf0;
	return in;
}