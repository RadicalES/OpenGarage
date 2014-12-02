/*
 * sm.c
 *
 * Created: 2014/11/23 09:50:17 AM
 *  Author: JanZwiegers
 */

#include <asf.h>
#include "uart.h"
#include "inputs.h"
#include "relays.h"

#define SM_LONG_DELAY 5000
#define SM_SHORT_DELAY 2000
#define SM_START_DELAY 5000
#define SM_TIMEOUT 30000

#define SM_STATE_INIT 0
#define SM_STATE_CLOSING 2
#define SM_STATE_CLOSE_DELAY 3
#define SM_STATE_CLOSED 4
#define SM_STATE_OPENING 5
#define SM_STATE_OPEN_DELAY 6
#define SM_STATE_OPEN 7
#define SM_STATE_MIDCLOSED_DELAY 8
#define SM_STATE_MIDCLOSED 9
#define SM_STATE_MIDOPEN_DELAY 10
#define SM_STATE_MIDOPEN 11

static uint8_t sm_state;
static uint16_t sm_timer;
static uint16_t sm_timeout;
static uint16_t sm_light_timer;

void sm_init( void )
{
	uint8_t v = inputs_get_value();
	sm_state = SM_STATE_INIT;
	sm_timer = 0;
	sm_timeout = 0;
	sm_light_timer = 0;
	relays_clr_channel();
}

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

static uint8_t sm_state_close_delay( void )
{
	if(sm_timer >= SM_LONG_DELAY ) {
		return SM_STATE_CLOSED;
	}
	return SM_STATE_CLOSE_DELAY;
}

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

static uint8_t sm_state_open_delay( void )
{
	if(sm_timer >= SM_LONG_DELAY ) {
		return SM_STATE_OPEN;
	}
	return SM_STATE_OPEN_DELAY;
}

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

static uint8_t sm_state_midopen_delay( void )
{
	if(sm_timer >= SM_SHORT_DELAY ) {
		return SM_STATE_MIDOPEN;
	}

	return SM_STATE_MIDOPEN_DELAY;
}

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

static uint8_t sm_state_midclosed_delay( void )
{
	if(sm_timer >= SM_SHORT_DELAY ) {
		return SM_STATE_MIDCLOSED;
	}

	return SM_STATE_MIDCLOSED_DELAY;
}

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

	if(sm_state != s) {
		uart_write_string("COS: ");
		uart_print_byte(sm_state);
		uart_write_string(" -> ");
		uart_print_byte(s);
		uart_write_string("\r\n");
	}

	sm_state = s;
}