#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef __AVR_ATtiny84__
#error "AVR not defined as ATtin84"
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#include "../I2C/I2C_slave.h"
#include "../Servo/Servo.h"

// buffer used to convert integer to string
char buffer[3];

int main(void){
	
	initTimer1Servo();
	I2C_init(0x32); // initalize as slave with address 0x32

	DDRB |= _BV(PB0) | _BV(PB2);
	PORTB |= _BV(PB0) | _BV(PB2);
	_delay_ms(1000);
	PORTB &= ~(1<<PB2);

	// allow interrupts
	sei();
	
	while(1){
		// convert receiver buffer index 0 to character array and send it via UART
		//itoa(rxbuffer[0], buffer, 10);
		//uart_puts(buffer);
		_delay_ms(1000);
		PORTB ^= ( 1 << PB0);
	}
	
	return 0;
}
