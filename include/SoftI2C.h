#ifndef SOFT_I2C_H
#define SOFT_I2C_H

#include <avr/io.h>

void i2c_start(void);

void i2c_stop(void);

void i2c_writebit(uint8_t val);

void i2c_writebyte(uint8_t byte);

void i2c_init(void);

#endif
