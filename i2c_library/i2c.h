#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

enum I2C_BIT_RATE {
    I2C_100000,
    I2C_400000
};

void i2c_master_init(unsigned char bit_rate);

volatile unsigned char operation;
volatile unsigned char slave_address;
volatile unsigned char bytes_to_write;
volatile unsigned char *byte_buffer;
volatile unsigned char bytes_sent;

void i2c_write(unsigned char address, unsigned char *bytes,
                unsigned char no_of_bytes);

void i2c_read(unsigned char address, unsigned char *bytes,
                unsigned char no_of_bytes);

#endif