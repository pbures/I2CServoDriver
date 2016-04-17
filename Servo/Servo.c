#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "Servo.h"

void initTimer1Servo(void) {
  OCR1A = PULSE_MID;
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12) | (1 << WGM13);
  TCCR1B |= (1 << CS11);  /* /8 prescaling -- counting in microseconds */
  ICR1 = 20000;                                    /* TOP value = 20ms */
  TCCR1A |= (1 << COM1A1);              /* Direct output on PB1 / OC1A */
  DDRB |= (1 << PB1);                            /* set pin for output */
}

int turnDegrees(uint16_t degrees) {
	if ((degrees < 0) || (degrees >180)) return 1;

	uint16_t pulseWidth = PULSE_MIN + ((PULSE_MAX - PULSE_MIN)/180 * degrees);
	OCR1A = pulseWidth;

	return 0;
}



