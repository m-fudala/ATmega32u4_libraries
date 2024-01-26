#include "i2c.h"

void i2c_init(struct I2C *i2c_struct, unsigned char address,
            unsigned char bit_rate) {
    i2c_struct->address = address;
    i2c_struct->bit_rate = bit_rate;

    if (i2c_struct->address) {
        // TODO: set address in slave mode 
    }

    switch (i2c_struct->bit_rate) {
        case I2C_100000: {
            TWBR = 72;

            break;
        }

        case I2C_400000: {
            TWBR = 12;

            break;
        }

        default: {
            return;
        }
    }

    TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
    TWCR |= (1 << TWIE);
}

void i2c_write(struct I2C *i2c_struct, unsigned char slave_address,
            unsigned char byte) {
    TWCR |= (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (_BV(TWINT))));

    if (TW_STATUS != TW_START) {
        return;
    }

    TWDR = slave_address | TW_WRITE;

    TWCR &= ~(1 << TWSTA);
    TWCR |= (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (_BV(TWINT))));

    switch (TW_STATUS) {
        case TW_MT_SLA_ACK: {
            if (TWCR & (1 << TWINT) >> TWINT) {
                TWDR = byte;

                TWCR |= (1 << TWINT) | (1 << TWEN);

                while (!(TWCR & (_BV(TWINT))));

                if (TW_STATUS == TW_MT_DATA_ACK) {
                    TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
                }
            }

            break;
        }

        case TW_MT_SLA_NACK: {
            return;
        }

        case TW_MR_ARB_LOST: {
            return;
        }

        default: {
            return;
        }
    }
}

void i2c_write_bytes(struct I2C *i2c_struct, unsigned char slave_address,
            unsigned char *bytes, unsigned char no_of_bytes) {
    TWCR |= (1 << TWSTA) | (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (_BV(TWINT))));

    if (TW_STATUS != TW_START) {
        return;
    }

    TWDR = slave_address | TW_WRITE;

    TWCR &= ~(1 << TWSTA);
    TWCR |= (1 << TWINT) | (1 << TWEN);

    while (!(TWCR & (_BV(TWINT))));

    switch (TW_STATUS) {
        case TW_MT_SLA_ACK: {
            for (unsigned char byte_i; byte_i < no_of_bytes; ++byte_i) {
                if (TWCR & (1 << TWINT) >> TWINT) {
                    TWDR = bytes[byte_i];

                    TWCR |= (1 << TWINT) | (1 << TWEN);

                    while (!(TWCR & (_BV(TWINT))));
                }
            }

            if (TW_STATUS == TW_MT_DATA_ACK) {
                TWCR |= (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
            }

            break;
        }

        case TW_MT_SLA_NACK: {
            return;
        }

        case TW_MR_ARB_LOST: {
            return;
        }

        default: {
            return;
        }
    }
}

ISR(TWI_vect) {
}
