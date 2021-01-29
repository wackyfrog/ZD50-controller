#include <avr/io.h>
#include "SoftI2C.h"
#include <util/delay.h>

#define I2C_PORT  PORTA
#define I2C_DDR   DDRA
#define SCK   _BV(1)
#define SDA   _BV(0)

#define I2C_SDA_LO    I2C_DDR |= SDA
#define I2C_SCK_LO    I2C_DDR |= SCK
#define I2C_SDA_HI    I2C_DDR &= ~(SDA)
#define I2C_SCK_HI    I2C_DDR &= ~(SCK)
#define I2C_WAIT      _delay_us(4)

void i2c_start(void) {
    I2C_SCK_HI;
    I2C_SDA_HI;
    I2C_SDA_LO;
    I2C_WAIT;
    I2C_SCK_LO;
    I2C_WAIT;
}

void i2c_stop(void) {
    I2C_SDA_LO;
    I2C_WAIT;
    I2C_SCK_HI;
    I2C_WAIT;
    I2C_SDA_HI;
    I2C_WAIT;
}

void i2c_writebit(uint8_t val) {
    if (val) { I2C_SDA_HI; }
    else { I2C_SDA_LO; }
    I2C_WAIT;
    I2C_SCK_HI;
    I2C_WAIT;
    I2C_SCK_LO;
}

void i2c_writebyte(uint8_t byte) {
    for (uint8_t i=0; i<8; i++) {
        i2c_writebit(byte & 0x80);
        byte <<= 1;
    }

    //Make sure you read the ACK
    I2C_SDA_HI;
    I2C_WAIT;
    I2C_SCK_HI;
    I2C_WAIT;
    //Read should be done on this line. Not using it yet so not doing read.
    I2C_SCK_LO;
    I2C_WAIT;

}

void i2c_cmd(uint8_t cmd) {
    i2c_start();
    i2c_writebyte(0x78);
    i2c_writebyte(0x80);
    i2c_writebyte(cmd);
    i2c_stop();
}

void i2c_init(void) {
    I2C_DDR &= ~(SCK | SDA);
}