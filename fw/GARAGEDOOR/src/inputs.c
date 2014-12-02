/**
 * Simple Automatic Garage Door Controller
 *
 * \file inputs.c
 *
 * \brief Opto Isolated and Digital Inputs
 * Init, service and manage all inputs. RTC scheduler needs to service
 * inputs on a regular interval.
 *
 * Copyright (C) 2014 Jan Zwiegers, jan@radialsystems.co.za
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <asf.h>
#include "uart.h"
#include "inputs.h"

#define INPUT_DEBOUNCE 20 //! 20 ms
#define TRIGGER_DEBOUNCE 1000 //! 1 sec

static uint16_t input_timers[8]; //! debounce timers
static uint8_t input_status; //! input last value

/*! init inputs value and timers */
void inputs_init( void )
{
	uint8_t c;
	input_status = 0;
	for(c=0; c<8; c++) {
		input_timers[c] = 0;
	}
}

/*! combine inputs into a single byte */
uint8_t inputs_get_value( void )
{
	uint8_t a = PINA & 0x0f;
	uint8_t d = PIND & 0x0c;
	uint8_t b = PINB & 0x03;
	uint8_t v = (a << 4) | (b) | (d);
	return v;
}

/*! called by RTC */
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

/*! exported function */
uint8_t inputs_get_status( void )
{
	uint8_t in = input_status;
	input_status &= 0xf0;
	return in;
}