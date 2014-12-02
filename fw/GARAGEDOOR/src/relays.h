/*
 * relays.h
 *
 * Created: 2014/11/22 07:31:20 PM
 *  Author: JanZwiegers
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