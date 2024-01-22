#include "i2c.h"

void i2c_init(struct I2C *i2c_struct, unsigned char address,
            unsigned char bit_rate) {
    i2c_struct->address = address;
    i2c_struct->bit_rate = bit_rate;

    if (i2c_struct->address) {
        // TODO: set address in slave mode 
    }

    switch (i2c_struct->bit_rate) {
        case I2C_100000:
        {
            TWBR = 72;

            break;
        }

        case I2C_400000:
        {
            TWBR = 12;

            break;
        }

        default: 
        {
            return;
        }
    }

    TWSR &= ~(1 << TWPS1) & ~(1 << TWPS0);
    TWCR |= (1 << TWEN) | (1 << TWIE);
}
