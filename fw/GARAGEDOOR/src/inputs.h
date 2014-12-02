/*
 * inputs.h
 *
 * Created: 2014/11/22 07:30:58 PM
 *  Author: JanZwiegers
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