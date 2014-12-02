/**
 * Simple Automatic Garage Door Controller
 *
 * \file uart.c
 *
 * \brief UART interface
 * Init & cont
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

#define BAUD_PRESCALE(BAUD) (((F_CPU / (BAUD * 16UL))) - 1)

//! ASCII representation of hexadecimal digits.
static const char HEX_DIGITS[16] = "0123456789ABCDEF";

/*! setup uart registers */
void uart_init( uint16_t buadrate )
{
	// Set baud rate
	UBRRL = BAUD_PRESCALE(buadrate);// Load lower 8-bits into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE(buadrate) >> 8);

	// Enable receiver and transmitter
	//UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
	UCSRB = ((1<<TXEN)|(1<<RXEN));

	//UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
}

/*! output a single character */
void uart_write_char( char c )
{
	while ((UCSRA & (1 << UDRE)) == 0) {}; //wait for last TX char to exit
	UDR = c;
}

/*! output a text string until end of string is reached  */
void uart_write_string( char *str )
{
	while(*str != '\0') {
		uart_write_char(*str);
		str++;
	}
}

/*! convert a byte to string and output */
void uart_print_byte( uint8_t b )
{
	char tmp[4];
	int i = sizeof(tmp) - 1;

	// Convert the given number to an ASCII decimal representation.
	tmp[i] = '\0';
	do {
		tmp[--i] = '0' + b % 10;
		b /= 10;
	} while(b);

	// Transmit the resulting string with the given USART.
	uart_write_string(tmp + i);
}

/*! convert a byte to hex and output */
void uart_print_byte_hex( uint8_t b )
{
	char tmp[3];
	int i;

	// Convert the given number to an ASCII hexadecimal representation.
	tmp[2] = '\0';
	for (i = 1; i >= 0; i--)
	{
		tmp[i] = HEX_DIGITS[b & 0xF];
		b >>= 4;
	}

	// Transmit the resulting string with the given USART.
	uart_write_string(tmp);
}
