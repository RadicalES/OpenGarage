/*
 * uart.h
 *
 * Created: 2014/11/21 10:16:06 PM
 *  Author: JanZwiegers
 */


#ifndef UART_H_
#define UART_H_

void uart_init( uint16_t buadrate );
void uart_write_char( char c );
void uart_write_string( char *str );
void uart_print_byte( uint8_t b );
void uart_print_byte_hex( uint8_t b );

#endif /* UART_H_ */