/**
 * Simple Automatic Garage Door Controller
 *
 * \file sm.c
 *
 * \brief State Machine
 * This is the main logic engine of the garage door controller
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
#include "relays.h"

#define SM_LONG_DELAY 5000 //! 5 sec
#define SM_SHORT_DELAY 2000 //! 2 sec
#define SM_START_DELAY 5000 //! start up delay
#define SM_TIMEOUT 30000 //! operation timeout

#define SM_STATE_INIT 0 //! initialize the SM
#define SM_STATE_CLOSING 2 //! door closing operation
#define SM_STATE_CLOSE_DELAY 3 //! end of closing, delay process
#define SM_STATE_CLOSED 4 //! door closed state
#define SM_STATE_OPENING 5 //! door is opening
#define SM_STATE_OPEN_DELAY 6 //! door is open, delay process
#define SM_STATE_OPEN 7 //! door open state
#define SM_STATE_MIDCLOSED_DELAY 8 //! mid closed process delay
#define SM_STATE_MIDCLOSED 9 //! door was closing and got stopped, next state will be opening
#define SM_STATE_MIDOPEN_DELAY 10 //! mid open process delay
#define SM_STATE_MIDOPEN 11 //! door was opening and got stopped

static uint8_t sm_state; //! state machine state
static uint16_t sm_timer; //! state machine timer
static uint16_t sm_timeout; //! state machine timeout
static uint16_t sm_light_timer; //! state machine light timer

/*! initialize state machine */
void sm_init( void )
{
	uint8_t v = inputs_get_value();
	sm_state = SM_STATE_INIT;
	sm_timer = 0;
	sm_timeout = 0;
	sm_light_timer = 0;
	relays_clr_channel();
}

/*! SM_STATE_INIT service routine */
static uint8_t sm_state_init( void )
{
	if(sm_timer >= SM_START_DELAY) {
		uint8_t in = inputs_get_status();
		sm_timer = 0;
		uart_write_string("SM Init: 0x");
		uart_print_byte_hex(in);
		uart_write_string("\r\n");

		if((in & INPUT_CLOSE_BIT) == INPUT_CLOSE_BIT) {
			return SM_STATE_CLOSED;
		}
		else if((in & INPUT_OPEN_BIT) == INPUT_OPEN_BIT) {
			return SM_STATE_OPEN;
		}

		return SM_STATE_MIDCLOSED;
	}

	return SM_STATE_INIT;
}

/*! SM_STATE_OPEN service routine */
static uint8_t sm_state_open( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		sm_timeout = 0;
		relays_set_channel(1);
		return SM_STATE_CLOSING;
	}

	return SM_STATE_OPEN;
}

/*! SM_STATE_CLOSING service routine */
static uint8_t sm_state_closing( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_CLOSE_BIT) == INPUT_CLOSE_BIT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_CLOSE_DELAY;
	}
	else if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_MIDCLOSED_DELAY;
	}
	else if(sm_timeout >= SM_TIMEOUT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_MIDCLOSED_DELAY;
	}

	return SM_STATE_CLOSING;
}

/*! SM_STATE_CLOSED_DELAY service routine */
static uint8_t sm_state_close_delay( void )
{
	if(sm_timer >= SM_LONG_DELAY ) {
		return SM_STATE_CLOSED;
	}
	return SM_STATE_CLOSE_DELAY;
}

/*! SM_STATE_CLOSED service routine */
static uint8_t sm_state_closed( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		sm_timeout = 0;
		relays_set_channel(0);
		return SM_STATE_OPENING;
	}

	return SM_STATE_CLOSED;
}

/*! SM_STATE_OPENING service routine */
static uint8_t sm_state_opening( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_OPEN_BIT) == INPUT_OPEN_BIT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_OPEN_DELAY;
	}
	else if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_MIDOPEN_DELAY;
	}
	else if(sm_timeout >= SM_TIMEOUT) {
		sm_timer = 0;
		relays_clr_channel();
		return SM_STATE_MIDOPEN_DELAY;
	}

	return SM_STATE_OPENING;
}

/*! SM_STATE_OPEN_DELAY service routine */
static uint8_t sm_state_open_delay( void )
{
	if(sm_timer >= SM_LONG_DELAY ) {
		return SM_STATE_OPEN;
	}
	return SM_STATE_OPEN_DELAY;
}

/*! SM_STATE_MIDOPEN service routine */
static uint8_t sm_state_midopen( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		sm_timeout = 0;
		relays_set_channel(1);
		return SM_STATE_CLOSING;
	}

	return SM_STATE_MIDOPEN;
}

/*! SM_STATE_MIDOPEN_DELAY service routine */
static uint8_t sm_state_midopen_delay( void )
{
	if(sm_timer >= SM_SHORT_DELAY ) {
		return SM_STATE_MIDOPEN;
	}

	return SM_STATE_MIDOPEN_DELAY;
}

/*! SM_STATE_MIDCLOSED service routine */
static uint8_t sm_state_midclosed( void )
{
	uint8_t in = inputs_get_status();

	if((in & INPUT_TRIGGER_BIT) == INPUT_TRIGGER_BIT) {
		sm_timer = 0;
		sm_timeout = 0;
		relays_set_channel(0);
		return SM_STATE_OPENING;
	}

	return SM_STATE_MIDCLOSED;
}

/*! SM_STATE_MIDCLOSED_DELAY service routine */
static uint8_t sm_state_midclosed_delay( void )
{
	if(sm_timer >= SM_SHORT_DELAY ) {
		return SM_STATE_MIDCLOSED;
	}

	return SM_STATE_MIDCLOSED_DELAY;
}

/*! state machine execution routine, called by RTC scheduler */
void sm_service( uint8_t delay )
{
	uint8_t s = sm_state;

	sm_timer += delay;
	sm_timeout += delay;

	switch(s) {
	case SM_STATE_CLOSED:
		s = sm_state_closed();
		break;
	case SM_STATE_CLOSING:
		s = sm_state_closing();
		break;
	case SM_STATE_CLOSE_DELAY:
		s = sm_state_close_delay();
		break;
	case SM_STATE_OPEN:
		s = sm_state_open();
		break;
	case SM_STATE_OPENING:
		s = sm_state_opening();
		break;
	case SM_STATE_OPEN_DELAY:
		s = sm_state_open_delay();
		break;
	case SM_STATE_MIDCLOSED_DELAY:
		s = sm_state_midclosed_delay();
		break;
	case SM_STATE_MIDCLOSED:
		s = sm_state_midclosed();
		break;
	case SM_STATE_MIDOPEN_DELAY:
		s = sm_state_midopen_delay();
		break;
	case SM_STATE_MIDOPEN:
		s = sm_state_midopen();
		break;
	case SM_STATE_INIT:
	default:
		s = sm_state_init();
		break;
	}

	//! Print a change of state
	if(sm_state != s) {
		uart_write_string("COS: ");
		uart_print_byte(sm_state);
		uart_write_string(" -> ");
		uart_print_byte(s);
		uart_write_string("\r\n");
	}

	sm_state = s;
}