#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#ifndef __AVR_ATtiny84__
#error "AVR not defined as ATtin84"
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../UsiTwi/UsiTwiSlave.h"
#include "../Servo/Servo.h"

#define DEVICE_ADDRESS 0x27

int main() {
	/* The servo pulse width is controlled by OCR1B value in ms (500 -- 2000).
	 * As a I2C master for now use the I2CServoDriverMaster in eclipseArduino.
	 * I do not have twi master code without Arduino libs.
	 */

	/* Those two pins are used for debugging! */
	DDRB = (1 << PB0) | (1 << PB1);

	for (int i = 0; i < 2; i++) {
		PORTB |= ((1 << PB0) | (1 << PB1));
		_delay_ms(300);
		PORTB &= ~((1 << PB0) | (1 << PB1));
		_delay_ms(300);
	}

	/* Init Timer1 for servo and USI device for TWI */
	initTimer1Servo();
	usiTwiSlaveInit(DEVICE_ADDRESS);
	sei();

	while (1) {
		/* TODO:
		 * Probably we can put ATTiny84 to sleep after
		 * giving some time to server to move to the right
		 * position.
		 */
	}

	return 0;
}
