/**
 * Simple Automatic Garage Door Controller
 *
 * \file main.c
 *
 * \brief Main source file
 *
 * Copyright (C) 2014 Radical Electronic Systems
 * Written by Jan Zwiegers, jan@radialsystems.co.za
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
#include "rtc.h"
#include "sm.h"
#include "inputs.h"
#include "relays.h"

#define BAUDRATE 38400 //! Serial port baudrate for debugging

static void port_init( void )
{
	// relay output pins - PD4-7
	DDRD = 0xf0;
	PORTD = 0x00;

	// LEDs output pins - PB4-7
	DDRB = 0xf0;
	PORTB = 0x00;

	// PA0-3 digital inputs - enable pull ups
	PORTA = 0x0f;
}

/*! main start */
int main (void)
{
	cpu_irq_disable();
	sysclk_init();
	port_init();
	uart_init(BAUDRATE);
	rtc_init();
	relays_init();
	inputs_init();
	uart_write_string("Garage Door Controller Starting...\r\n");
	uart_write_string("Version 1.0\r\n");
	sm_init();
	rtc_start();
	cpu_irq_enable();
	uart_write_string("RTC scheduler starting...\r\n");
	rtc_service();
}
