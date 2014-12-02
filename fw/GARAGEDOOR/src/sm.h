/**
 * Simple Automatic Garage Door Controller
 *
 * \file sm.h
 *
 * \brief State Machine
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


#ifndef SM_H_
#define SM_H_

void sm_init( void );
void sm_service( uint8_t delay );


#endif /* SM_H_ */