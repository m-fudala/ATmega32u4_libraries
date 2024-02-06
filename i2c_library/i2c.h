#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/twi.h>

// enum I2C_ADDRESS {
//     MASTER
// };

enum I2C_BIT_RATE {
    I2C_100000,
    I2C_400000
};

// typedef struct I2C {
//     unsigned char address;
//     unsigned char bit_rate;
// } I2C;

void i2c_master_init(unsigned char bit_rate);

void i2c_write(unsigned char slave_address, unsigned char byte);

void send_start();

void react_to_codes();

// void i2c_write_bytes(unsigned char slave_address, unsigned char *bytes,
//                     unsigned char no_of_bytes);

#endif