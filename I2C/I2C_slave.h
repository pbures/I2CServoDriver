#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

volatile uint8_t data[2];
volatile uint8_t dataIndex;

void I2C_init(uint8_t address);
void I2C_stop(void);
ISR(TWI_vect);

#endif // I2C_SLAVE_H
