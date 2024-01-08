#include "gpio.h"

void pin_init(struct Pin *pin_struct, char port, char pin,
            char direction, char pull_up) {
    pin_struct->port = port;
    pin_struct->pin = pin;
    pin_struct->direction = direction;
    pin_struct->pull_up = pull_up;
    
    if (pin_struct->direction == OUTPUT) {
        DDRC |= 1 << pin_struct->pin;
    }
    else if (pin_struct->direction == INPUT) {
        DDRC &= ~(1 << pin_struct->pin);
    }
}

void pin_write(struct Pin *pin_struct, char state) {
    if (pin_struct->direction == OUTPUT) {
        if (state == HIGH) {
            PORTC |= 1 << pin_struct->pin;
        }
        else if (state == LOW) {
            PORTC &= ~(1 << pin_struct->pin);
        }
        else {
            // TODO
        }
    }
    else {
        // TODO
    }
}
