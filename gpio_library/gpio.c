#include "gpio.h"

unsigned char pin_init(struct Pin *pin_struct, volatile unsigned char *port,
                        unsigned char pin, unsigned char direction) {
    pin_struct->port = (unsigned char *) port;
    pin_struct->pin_and_direction = pin | (direction << 4);

    if (pin_struct->port == (unsigned char *) &PORTB) {
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
        return PIN_INIT_INVALID_PORT;
    }

    if ((pin_struct->pin_and_direction >> 4) > INPUT_PULLUP) {
        return PIN_INIT_INVALID_DIRECTION;
    }

    switch (pin_struct->pin_and_direction >> 4) {
        case OUTPUT: {
            *pin_struct->direction_reg |=
                1 << (pin_struct->pin_and_direction & PIN_MASK);

            break;
        }
        
        case INPUT: {
            *pin_struct->direction_reg &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
            *pin_struct->port &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));

            break;
        }

        case INPUT_PULLUP: {
            *pin_struct->direction_reg &=
                ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
            *pin_struct->port |=
                1 << (pin_struct->pin_and_direction & PIN_MASK);

            break;
        }
    }

    return PIN_INIT_OK;
}

unsigned char pin_write(struct Pin *pin_struct, unsigned char state) {
    if ((pin_struct->pin_and_direction >> 4) != OUTPUT) {
        return PIN_WRITE_INVALID_DIRECTION;
    } else if (state > HIGH) {
        return PIN_WRITE_INVALID_STATE;
    }

    if (state == HIGH) {
        *pin_struct->port |= 1 << (pin_struct->pin_and_direction & PIN_MASK);
    } else if (state == LOW) {
        *pin_struct->port &=
            ~(1 << (pin_struct->pin_and_direction & PIN_MASK));
    }

    return PIN_WRITE_OK;
}

unsigned char pin_read(struct Pin *pin_struct) {
    return (*pin_struct->pin_reg &
        (1 << (pin_struct->pin_and_direction & PIN_MASK))) >>
        (pin_struct->pin_and_direction & PIN_MASK);
}

void pin_toggle(struct Pin *pin_struct) {
    *pin_struct->pin_reg |= 1 << (pin_struct->pin_and_direction & PIN_MASK);
}

void global_pullup_disable() {
    MCUCR |= 1 << PUD;
}

void global_pullup_enable() {
    MCUCR &= ~(1 << PUD);
}
