/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "uart.h"
#include "rtc.h"
#include "sm.h"
#include "inputs.h"
#include "relays.h"

#define BAUDRATE 38400

int main (void)
{
	cpu_irq_disable();
	board_init();
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
