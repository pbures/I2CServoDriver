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

int main() {
	/* TODO:
	 * The servo init code is fixed, the width is controlled by OCR1B value in ms (500 -- 2000).
	 * I have managed to run it in ATTiny84Blink, test it here with the I2C in place.
	 *
	 * As a I2C master for now use the _2016_I2cServoMaster sketch which sends two byte
	 * number based on input from serial console.
	 *
	 */
	DDRB = (1 << PB0) | (1 << PB1);

	for (int i = 0; i < 2; i++) {
		PORTB |= ((1 << PB0) | (1 << PB1));
		_delay_ms(300);
		PORTB &= ~((1 << PB0) | (1 << PB1));
		_delay_ms(300);
	}

	initTimer1Servo();
	usiTwiSlaveInit(0x27);
	sei();

	turnDegrees(0);
	_delay_ms(300);
	turnDegrees(90);
	_delay_ms(300);
	turnDegrees(180);
	_delay_ms(300);


//	uint8_t data[2];
//	uint8_t index = 0;
//
//	data[0] = 0;
//	data[1] = 0;

	while (1) {

//		if (usiTwiDataInReceiveBuffer())
//			data[index++] = usiTwiReceiveByte();
//
//		if (index > 1) {
//			uint16_t val = data[1] * 256 + data[0];
//
//			for (int i = 0; i < val; i++) {
//				PORTB = 0x0;
//				_delay_ms(50);
//				PORTB = (1 << PB1);
//				_delay_ms(50);
//			}
//
//			for (int i = 0; i < 3; i++) {
//				PORTB |= ((1 << PB0) | (1 << PB1));
//				_delay_ms(300);
//				PORTB &= ~((1 << PB0) | (1 << PB1));
//				_delay_ms(300);
//			}
//
//			turnDegrees(val);
//
//			index = 0;
//			data[0] = 0;
//			data[1] = 1;
//		}
//
//		PORTB = (1 << PB0);
//		_delay_ms(50);
//		PORTB = (1 << PB1);
//		_delay_ms(50);

		_delay_ms(1000);
	}

	return 0;
}
