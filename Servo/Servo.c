#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "../Util/utils.h"
#include "Servo.h"

void initTimer1Servo(void) {
	/* Need a PWM output on OC1B (PA5) pin, or OC0A (PB2).
	 OC1B: Output Compare Match output: The PA5 pin can serve as an external output for the
	 Timer/Counter1 Compare Match B. The PA5 pin has to be configured as an output (DDA5 set
	 (one)) to serve this function. The OC1B pin is also the output pin for the PWM mode timer
	 function
	 */

	/* Use PA5 (OC1B PWM Pin) */
	DDRA = (1 << PA5);

	/* Fast PWM with ICR1 as TOP. See Page 110, Table 12-5. */
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	/* /8 prescaling -- counting in microseconds. See Page 112, Table 12-6. */
	TCCR1B |= (1 << CS11);

	/* TOP value = 20ms */
	ICR1 = 20000;

	/* Direct output on OC1B (PA5) pin. Page 108 */
	TCCR1A |= (1 << COM1B1);

	/* Set the pulse length to middle position for start */
	OCR1B = PULSE_MID;
}

int turnDegrees(uint16_t degrees) {
	if ((degrees < 0) || (degrees > 180)) {
		return 1;
	}

	uint16_t pulseWidth = PULSE_MIN + ((PULSE_MAX - PULSE_MIN) / 180 * degrees);
	OCR1B = pulseWidth;

	return 0;
}

