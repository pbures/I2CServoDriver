/*
 * utils.c
 *
 *  Created on: 20. 4. 2016
 *      Author: pbures
 */
#include "utils.h"

void blinkLed(int led1count, int led2count, uint16_t delay) {
	DDRB |= ((1 << PB0) | (1 << PB1));
	for (int i = 0; i < led1count; i++) {
		PORTB |= (1 << PB0);
		_delay_ms(delay / 2);
		PORTB &= ~(1 << PB0);
		_delay_ms(delay / 2);
	}
	for (int i = 0; i < led2count; i++) {
		PORTB |= (1 << PB1);
		_delay_ms(delay / 2);
		PORTB &= ~(1 << PB1);
		_delay_ms(delay / 2);
	}
}
