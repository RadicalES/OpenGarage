/*
 * rtc.c
 *
 * Created: 2014/11/22 09:53:44 AM
 *  Author: JanZwiegers
 */

#include <asf.h>
#include "uart.h"
#include "inputs.h"
#include "sm.h"
#include "relays.h"
#include "rtc.h"

/*
* REGISTERS : 8-bit Timer Counter 2
* TCCR2 - control reg
*
*
*/

/* macro to calculate a 1 ms tick */
#define OCR2_VALUE (F_CPU / 64) / 1000

static volatile uint32_t rtc_ticks;
static volatile uint8_t rtc_events;

ISR(TIMER2_COMP_vect)
{
	rtc_ticks++;
	rtc_events++;
}

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

void rtc_start()
{
	TCNT2 = 0;
	//enable interrupts
	TIMSK |= 1 << OCIE2;
	TIFR |= 1 << OCF2;
}

void rtc_service( void )
{
	while(1) {
		if(rtc_events > 0) {
			if((rtc_ticks % 500) == 0) { // 1/2 sec tick
				relays_toggle_run();
			}
			else if((rtc_ticks % 10) == 2) { // 10 ms tick at 2 interfval
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