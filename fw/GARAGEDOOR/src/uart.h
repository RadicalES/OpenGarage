/**
 * Simple Automatic Garage Door Controller
 *
 * \file uart.h
 *
 * \brief UART header file
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


#ifndef UART_H_
#define UART_H_

void uart_init( uint16_t buadrate );
void uart_write_char( char c );
void uart_write_string( char *str );
void uart_print_byte( uint8_t b );
void uart_print_byte_hex( uint8_t b );

#endif /* UART_H_ */