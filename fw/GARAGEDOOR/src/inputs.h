/**
 * Simple Automatic Garage Door Controller
 *
 * \file inputs.h
 *
 * \brief inputs header file
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


#ifndef INPUTS_H_
#define INPUTS_H_

#define INPUT_OPEN 1
#define INPUT_OPEN_BIT 1 << INPUT_OPEN
#define INPUT_CLOSE 0
#define INPUT_CLOSE_BIT 1 << INPUT_CLOSE
#define INPUT_TRIGGER 2
#define INPUT_TRIGGER_BIT 1 << INPUT_TRIGGER
#define INPUT_LIGHT 3
#define INPUT_LIGHT_BIT 1 << INPUT_LIGHT

void inputs_init( void );
void inputs_service( uint8_t delay );
uint8_t inputs_get_status( void );
uint8_t inputs_get_value( void );

#endif /* INPUTS_H_ */