#include "i2c.h"

void i2c_master_init(unsigned char bit_rate) {
    operation = 0;
    slave_address = 0;
    bytes_to_write = 0;
    byte_buffer = 0;
    bytes_sent = 0;

    cli();

    switch (bit_rate) {
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

    TWSR &= ~(_BV(TWPS1) | _BV(TWPS0));
    TWCR |= _BV(TWIE);

    sei();
}

void i2c_write(unsigned char address, unsigned char *bytes,
                unsigned char no_of_bytes) {
    operation = TW_WRITE;
    slave_address = address;
    byte_buffer = bytes;
    bytes_to_write = no_of_bytes;

    TWCR |= _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
}

void i2c_read(unsigned char address, unsigned char *bytes,
                unsigned char no_of_bytes) {
    operation = TW_READ;
    slave_address = address;
    byte_buffer = bytes;
    bytes_to_write = no_of_bytes;

    TWCR |= _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
}

ISR(TWI_vect) {
    switch (TW_STATUS) {
        case TW_START: {
            TWDR = slave_address | operation;

            TWCR &= ~_BV(TWSTA);
            TWCR |= _BV(TWINT) | _BV(TWEN);

            break;
        }

        case TW_MT_SLA_ACK: {
            if (TWCR & _BV(TWINT) >> TWINT) {
                TWDR = byte_buffer[bytes_sent];

                ++bytes_sent;

                TWCR |= _BV(TWINT) | _BV(TWEN);
            }

            break;
        }

        case TW_MR_SLA_ACK: {
            if (TWCR & _BV(TWINT) >> TWINT) {
                TWDR = byte_buffer[bytes_sent];

                ++bytes_sent;

                TWCR |= _BV(TWINT) | _BV(TWEN);
            }

            break;
        }

        case TW_MT_DATA_ACK: {
            if (!(bytes_sent == bytes_to_write)) {
                TWDR = byte_buffer[bytes_sent];

                ++bytes_sent;

                TWCR |= _BV(TWINT) | _BV(TWEN);
            } else {
                TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
                bytes_sent = 0;
            }

            break;
        }

        case TW_MR_DATA_ACK: {
            if (!(bytes_sent == bytes_to_write)) {
                TWDR = byte_buffer[bytes_sent];

                ++bytes_sent;

                TWCR |= _BV(TWINT) | _BV(TWEN);
            } else {
                TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
                bytes_sent = 0;
            }

            break;
        }

        case TW_MT_SLA_NACK: {
            return;
        }

        case TW_MR_SLA_NACK: {
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
