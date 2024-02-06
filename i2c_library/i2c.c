#include "i2c.h"

void i2c_master_init(unsigned char bit_rate) {
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

void i2c_write(unsigned char slave_address, unsigned char byte) {
    // TWCR |= _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);

    send_start();

    // while (!(TWCR & (_BV(TWINT))));

    // if (TW_STATUS != TW_START) {
    //     return;
    // }

    // TWDR = slave_address | TW_WRITE;

    // TWCR &= ~_BV(TWSTA);
    // TWCR |= _BV(TWINT) | _BV(TWEN);

    // while (!(TWCR & (_BV(TWINT))));

    // switch (TW_STATUS) {
    //     case TW_MT_SLA_ACK: {
    //         if (TWCR & _BV(TWINT) >> TWINT) {
    //             TWDR = byte;

    //             TWCR |= _BV(TWINT) | _BV(TWEN);

    //             while (!(TWCR & (_BV(TWINT))));

    //             if (TW_STATUS == TW_MT_DATA_ACK) {
    //                 TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
    //             }
    //         }

    //         break;
    //     }

    //     case TW_MT_SLA_NACK: {
    //         return;
    //     }

    //     case TW_MR_ARB_LOST: {
    //         return;
    //     }

    //     default: {
    //         return;
    //     }
    // }
}

void send_start() {
    TWCR |= _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);
}

void react_to_codes() {
    // if (TW_STATUS != TW_START) {
    //     return;
    // }

    // while (!(TWCR & (_BV(TWINT))));

    switch (TW_STATUS) {
        case TW_START: {
            // TWDR = slave_address | TW_WRITE;
            TWDR = (8 << 1) | TW_WRITE;

            TWCR &= ~_BV(TWSTA);
            TWCR |= _BV(TWINT) | _BV(TWEN);

            break;
        }

        case TW_MT_SLA_ACK: {
            if (TWCR & _BV(TWINT) >> TWINT) {
                // TWDR = byte;
                TWDR = '0';

                TWCR |= _BV(TWINT) | _BV(TWEN);

                // while (!(TWCR & (_BV(TWINT))));

                // if (TW_STATUS == TW_MT_DATA_ACK) {
                //     TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
                // }
            }

            break;
        }

        case TW_MT_DATA_ACK: {
            TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);

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

// void i2c_write_bytes(unsigned char slave_address, unsigned char *bytes,
//                     unsigned char no_of_bytes) {
//     TWCR |= _BV(TWSTA) | _BV(TWINT) | _BV(TWEN);

//     while (!(TWCR & (_BV(TWINT))));

//     if (TW_STATUS != TW_START) {
//         return;
//     }

//     TWDR = slave_address | TW_WRITE;

//     TWCR &= ~_BV(TWSTA);
//     TWCR |= _BV(TWINT) | _BV(TWEN);

//     while (!(TWCR & (_BV(TWINT))));

//     switch (TW_STATUS) {
//         case TW_MT_SLA_ACK: {
//             for (unsigned char byte_i; byte_i < no_of_bytes; ++byte_i) {
//                 if (TWCR & _BV(TWINT) >> TWINT) {
//                     TWDR = bytes[byte_i];

//                     TWCR |= _BV(TWINT) | _BV(TWEN);

//                     while (!(TWCR & (_BV(TWINT))));
//                 }
//             }

//             if (TW_STATUS == TW_MT_DATA_ACK) {
//                 TWCR |= _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
//             }

//             break;
//         }

//         case TW_MT_SLA_NACK: {
//             return;
//         }

//         case TW_MR_ARB_LOST: {
//             return;
//         }

//         default: {
//             return;
//         }
//     }
// }

ISR(TWI_vect) {
    react_to_codes();
}
