/**
 * Simple Automatic Garage Door Controller
 *
 * \file rtc.c
 *
 * \brief RTC scheduler
 * Scheduler provides timing and service our various interfaces.
 * Also keeps our state machine going
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
#include "inputs.h"
#include "sm.h"
#include "relays.h"
#include "rtc.h"

#define OCR2_VALUE (F_CPU / 64) / 1000 //! macro to calculate a 1ms tick

static volatile uint32_t rtc_ticks; //! ticks since boot
static volatile uint8_t rtc_events; //! indicate a tick event

/*! RTC interrupt */
ISR(TIMER2_COMP_vect)
{
	rtc_ticks++;
	rtc_events++;
}

/*! init RTC system */
void rtc_init()
{
	// setup clock, pre-scaled 64, CTC mode
	TCCR2 = (0 << CS20 | 0 << CS21 | 1 << CS22) | (0 << WGM20 | 1 << WGM21) | (0 << COM21 | 1 << COM20);

	// reset count
	TCNT2 = 0;
	rtc_ticks = 0;

	// set compare match value for 1 ms
	OCR2 = OCR2_VALUE;
}

/*! start RTC system */
void rtc_start()
{
	TCNT2 = 0;
	//enable interrupts
	TIMSK |= 1 << OCIE2;
	TIFR |= 1 << OCF2;
}

/*! endless loop to service RTC events*/
void rtc_service( void )
{
	while(1) {
		if(rtc_events > 0) { // only execute when need to
			if((rtc_ticks % 500) == 0) { // 1/2 sec tick
				relays_toggle_run();
			}
			else if((rtc_ticks % 10) == 2) { // 10 ms tick at 2 interval
				inputs_service(10);
			}
			else if((rtc_ticks % 10) == 4) {
				sm_service(10);
			}
			else if((rtc_ticks % 10) == 6) {
			}
			rtc_events = 0;
		}
	}
}