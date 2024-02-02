#include "gpio.h"

void pin_init(struct Pin *pin_struct, volatile unsigned char *port,
            unsigned char pin, unsigned char direction) {
    pin_struct->port = (unsigned char *) port;
    pin_struct->pin = pin;
    pin_struct->direction = direction;

    if (pin_struct->port == &PORTB) {
        pin_struct->direction_reg = (unsigned char *) &DDRB;
        pin_struct->pin_reg = (unsigned char *) &PINB;
    } else if (pin_struct->port == (unsigned char *) &PORTC) {
        pin_struct->direction_reg = (unsigned char *) &DDRC;
        pin_struct->pin_reg = (unsigned char *) &PINC;
    } else if (pin_struct->port == (unsigned char *) &PORTD) {
        pin_struct->direction_reg = (unsigned char *) &DDRD;
        pin_struct->pin_reg = (unsigned char *) &PIND;
    } else if (pin_struct->port == (unsigned char *) &PORTE) {
        pin_struct->direction_reg = (unsigned char *) &DDRE;
        pin_struct->pin_reg = (unsigned char *) &PINE;
    } else if (pin_struct->port == (unsigned char *) &PORTF) {
        pin_struct->direction_reg = (unsigned char *) &DDRF;
        pin_struct->pin_reg = (unsigned char *) &PINF;
    }

    switch (pin_struct->direction) {
        case OUTPUT: {
            *pin_struct->direction_reg |= 1 << pin_struct->pin;

            break;
        }
        
        case INPUT: {
            *pin_struct->direction_reg &= ~(1 << pin_struct->pin);
            *pin_struct->port &= ~(1 << pin_struct->pin);

            break;
        }

        case INPUT_PULLUP: {
            *pin_struct->direction_reg &= ~(1 << pin_struct->pin);
            *pin_struct->port |= 1 << pin_struct->pin;

            break;
        }
    }   
}

unsigned char pin_write(struct Pin *pin_struct, unsigned char state) {
    if (pin_struct->direction != OUTPUT) {
        return PIN_WRITE_INVALID_DIRECTION;
    } else if (state > HIGH) {
        return PIN_WRITE_INVALID_STATE;
    }

    if (state == HIGH) {
        *pin_struct->port |= 1 << pin_struct->pin;
    } else if (state == LOW) {
        *pin_struct->port &= ~(1 << pin_struct->pin);
    }

    return PIN_WRITE_OK;
}

unsigned char pin_read(struct Pin *pin_struct) {
    unsigned char pin_read_state = 0;
    unsigned char read_mask = 1 << pin_struct->pin;

    return pin_read_state = (*pin_struct->pin_reg & read_mask)
                             >> pin_struct->pin;
}

void pin_toggle(struct Pin *pin_struct) {
    *pin_struct->pin_reg |= 1 << pin_struct->pin;
}

void global_pullup_disable() {
    MCUCR |= 1 << PUD;
}

void global_pullup_enable() {
    MCUCR &= ~(1 << PUD);
}
