#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2C_slave.h"
#include "../Servo/Servo.h"

void I2C_init(uint8_t address){
	/* Page  223:
	 * To initiate the Slave Receiver mode, TWAR and TWCR must be initialized as follows.
	 *
	 * The upper 7 bits are the address to which the 2-wire Serial Interface will respond
	 * when addressed by a Master. If the LSB is set, the TWI will respond to the general
	 * call address (0x00), otherwise it will ignore the general call address.
	 *
	 * TWEN must be written to one to enable the TWI. The TWEA bit must be written to one
	 * to enable the acknowledgment of the device’s own slave address or the general call
	 * address. TWSTA and TWSTO must be written to zero. TWIE to enable interrupt, TWEN to
	 * enable the TW device.
	 */

	TWAR = address << 1;
	TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

void I2C_stop(void){
	// clear acknowledge and enable bits
	TWCR &= ~( (1<<TWEA) | (1<<TWEN) );
}

/*
 * Master will send data in the following structure:
 * Two bytes are accepted, giving out the degrees where to turn.
 * MSB then LSB are sent.
 */

ISR(TWI_vect){

	// This device has been acknowledged,prepare for transfer.
	if( (TWSR & 0xF8) == TW_SR_SLA_ACK ){
		data[0] = 0; data[1] = 0; dataIndex=0;
		PORTB ^= _BV(PB2);
		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}

    // Receive data.
	else if( (TWSR & 0xF8) == TW_SR_DATA_ACK ){ // data has been received in slave receiver mode
		PORTB ^= _BV(PB2);

		if (dataIndex <= 1){
			data[dataIndex++] = TWDR;
		}

		if (dataIndex == 2){
			turnDegrees((uint16_t)data[1]*256+data[0]);
		}

		TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	}

    // Get ready for next receive.
	else {
		TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
	}
}
