/**
 * Simple Automatic Garage Door Controller
 *
 * \file relays.h
 *
 * \brief Relay control header file
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


#ifndef RELAYS_H_
#define RELAYS_H_

void relays_init( void );
void relays_set_outputs( uint8_t value );
uint8_t relays_get_outputs( void );
uint8_t relays_toggle_run( void );
void relays_set_channel( uint8_t index );
void relays_clr_channel( void );

#endif /* RELAYS_H_ */