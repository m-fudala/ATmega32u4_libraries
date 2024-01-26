#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

enum I2C_ADDRESS {
    MASTER
};

enum I2C_BIT_RATE {
    I2C_100000,
    I2C_400000
};

typedef struct I2C {
    unsigned char address;
    unsigned char bit_rate;
} I2C;

void i2c_init(struct I2C *i2c_struct, unsigned char address,
            unsigned char bit_rate);

void i2c_write(struct I2C *i2c_struct, unsigned char slave_address,
            unsigned char byte);

#endif