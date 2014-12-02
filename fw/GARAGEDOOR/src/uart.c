/*
 * uart.c
 *
 * Created: 2014/11/21 10:15:52 PM
 *  Author: JanZwiegers
 */

#include <asf.h>

#define BAUD_PRESCALE(BAUD) (((F_CPU / (BAUD * 16UL))) - 1)
//#define USART_BAUDRATE 38400
//#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

//! ASCII representation of hexadecimal digits.
static const char HEX_DIGITS[16] = "0123456789ABCDEF";

void uart_init( uint16_t buadrate )
{
	// Set baud rate
	UBRRL = BAUD_PRESCALE(buadrate);// Load lower 8-bits into the low byte of the UBRR register
	UBRRH = (BAUD_PRESCALE(buadrate) >> 8);

	// Enable receiver and transmitter and receive complete interrupt
	//UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
	UCSRB = ((1<<TXEN)|(1<<RXEN));

	//UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); // Use 8-bit character sizes
}


void uart_write_char( char c )
{
	while ((UCSRA & (1 << UDRE)) == 0) {}; // Do nothing until UDR is ready for more data to be written to it
	UDR = c;//ReceivedByte; // Echo back the received byte back to the computer
}

void uart_write_string( char *str )
{
	while(*str != '\0') {
		uart_write_char(*str);
		str++;
	}
}

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
