/**
 * Simple Automatic Garage Door Controller
 *
 * \file relays.c
 *
 * \brief Relay control
 * Init & control relays
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
#include "relays.h"

static volatile uint8_t relays; //! relays local status

/*! control relays pins on various ports */
void relays_set_outputs( uint8_t value )
{
	relays = value;
	PORTD = (value << 4) & 0xf0;
	PORTB = value & 0xf0;
}

/*! switch a relay channel on */
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

/*! switch all relay channels off */
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

/*! init relays interface */
void relays_init()
{
	relays = 0x00;
	relays_set_outputs(relays);
}

/*! read relay status */
uint8_t relays_get_outputs( void )
{
	return relays;
}

/*! toggle a run LED. One relay channel driver is connected to a LED
 *! we use this to show the activity of the state machine by toggeling
 *! it every 500 ms
 */
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