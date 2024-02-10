#include "gpio.h"

unsigned char pin_init(struct Pin *pin_struct, volatile unsigned char *port,
                        unsigned char pin, unsigned char direction) {
    pin_struct->port = (unsigned char *) port;
    pin_struct->pin_and_direction = pin | (direction << 4);

    // assign DDRx and PINx registers depending on provided port
    if (pin_struct->port == (unsigned char *) &PORTB) {
        // check if given pin number is possible
        if ((pin_struct->pin_and_direction & PIN_MASK) > 7) {
            return PIN_INIT_INVALID_PIN;
        }

        pin_struct->direction_reg = (unsigned char *) &DDRB;
        pin_struct->pin_reg = (unsigned char *) &PINB;
    } else if (pin_struct->port == (unsigned char *) &PORTC) {
        if (((pin_struct->pin_and_direction & PIN_MASK) > 7) || 
            ((pin_struct->pin_and_direction & PIN_MASK) < 6)) {
            return PIN_INIT_INVALID_PIN;
        }

        pin_struct->direction_reg = (unsigned char *) &DDRC;
        pin_struct->pin_reg = (unsigned char *) &PINC;
    } else if (pin_struct->port == (unsigned char *) &PORTD) {
        if ((pin_struct->pin_and_direction & PIN_MASK) > 7) {
            return PIN_INIT_INVALID_PIN;
        }

        pin_struct->direction_reg = (unsigned char *) &DDRD;
        pin_struct->pin_reg = (unsigned char *) &PIND;
    } else if (pin_struct->port == (unsigned char *) &PORTE) {
        if (((pin_struct->pin_and_direction & PIN_MASK) != 2) || 
            ((pin_struct->pin_and_direction & PIN_MASK) != 6)) {
            return PIN_INIT_INVALID_PIN;
        }

        pin_struct->direction_reg = (unsigned char *) &DDRE;
        pin_struct->pin_reg = (unsigned char *) &PINE;
    } else if (pin_struct->port == (unsigned char *) &PORTF) {
        if (((pin_struct->pin_and_direction & PIN_MASK) > 7) || 
            ((pin_struct->pin_and_direction & PIN_MASK) == 2) || 
            ((pin_struct->pin_and_direction & PIN_MASK) == 3)) {
            return PIN_INIT_INVALID_PIN;
        }
        
        pin_struct->direction_reg = (unsigned char *) &DDRF;
        pin_struct->pin_reg = (unsigned char *) &PINF;
    } else {
        return PIN_INIT_INVALID_PORT;   // when port was not recognized
    }

    // check for pin direction validity
    if ((pin_struct->pin_and_direction >> 4) > INPUT_PULLUP) {
        return PIN_INIT_INVALID_DIRECTION;
    }

    // configure pin's direction
    switch (pin_struct->pin_and_direction >> 4) {
        case OUTPUT: {
            *pin_struct->direction_reg |=
                1 << (pin_struct->pin_and_direction & PIN_MASK);
                                                // write 1 to DDRxn

            break;
        }
        
        case INPUT: {
            *pin_struct->direction_reg &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
                                                // write 0 to DDRxn
            *pin_struct->port &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
                                                // write 0 to PORTxn

            break;
        }

        case INPUT_PULLUP: {
            *pin_struct->direction_reg &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
                                                // write 0 to DDRxn
            *pin_struct->port |=
                1 << (pin_struct->pin_and_direction & PIN_MASK);
                                                // write 1 to PORTxn

            break;
        }
    }

    return PIN_INIT_OK;
}

unsigned char pin_write(struct Pin *pin_struct, unsigned char state) {
    // check if pin is not configured as output or if given state is invalid
    if ((pin_struct->pin_and_direction >> 4) != OUTPUT) {
        return PIN_WRITE_INVALID_DIRECTION;
    } else if (state > HIGH) {
        return PIN_WRITE_INVALID_STATE;
    }

    if (state == HIGH) {
        *pin_struct->port |= 1 << (pin_struct->pin_and_direction & PIN_MASK);
                                                // write 1 to PORTxn
    } else if (state == LOW) {
        *pin_struct->port &=
            ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
                                                // write 0 to PORTxn
    }

    return PIN_WRITE_OK;
}

unsigned char pin_read(struct Pin *pin_struct) {
    // (PINx & (1 << PINxn)) >> PINxn    (equals 0 or 1)
    // AND PINx with one shifted to PINxn, then shift pin number times to right
    // in order for return to be 0 or 1
    return (*pin_struct->pin_reg &
        (1 << (pin_struct->pin_and_direction & PIN_MASK))) >>
        (pin_struct->pin_and_direction & PIN_MASK);
}

void pin_toggle(struct Pin *pin_struct) {
    *pin_struct->pin_reg |= 1 << (pin_struct->pin_and_direction & PIN_MASK);
                                                // write 1 to PINxn
}
