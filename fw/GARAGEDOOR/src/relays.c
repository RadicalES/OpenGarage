/*
 * relays.c
 *
 * Created: 2014/11/22 07:31:07 PM
 *  Author: JanZwiegers
 */

#include <asf.h>
#include "uart.h"
#include "relays.h"

static volatile uint8_t relays;

void relays_set_outputs( uint8_t value )
{
	relays = value;
	PORTD = (value << 4) & 0xf0;
	PORTB = value & 0xf0;
}

void relays_set_channel( uint8_t index )
{
	uint8_t r = relays & 0xcc;
	if(index < 3) {
		r |= (0x11 << index);

		uart_write_string("relay set: ");
		uart_print_byte_hex(r);
		uart_write_string("\r\n");

		relays_set_outputs(r);
	}
}

void relays_clr_channel( )
{
	uint8_t r = relays & 0xcc;
	//if(index < 3) {
		//r |= (0x11 << index);

		uart_write_string("relay set: ");
		uart_print_byte_hex(r);
		uart_write_string("\r\n");

		relays_set_outputs(r);
	//}
}


void relays_init()
{
	relays = 0x00;
	relays_set_outputs(relays);
}

uint8_t relays_get_outputs( void )
{
	return relays;
}

uint8_t relays_toggle_run( void )
{
	uint8_t r = relays & 0x80;
	if(r == 0x80) {
		r = 0x7f & relays;
	}
	else {
		r = 0x80 | relays;
	}
	relays_set_outputs(r);
}