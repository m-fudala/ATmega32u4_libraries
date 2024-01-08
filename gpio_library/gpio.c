#include "gpio.h"

void pin_init(struct Pin *pin_struct, char port, char pin,
            char direction, char pull_up) {
    pin_struct->port = port;
    pin_struct->pin = pin;
    pin_struct->direction = direction;
    pin_struct->pull_up = pull_up;

    switch (pin_struct->port) {
        case PB:
        {
            if (pin_struct->direction == OUTPUT) {
                DDRB |= 1 << pin_struct->pin;
            }
            else if (pin_struct->direction == INPUT) {
                DDRB &= ~(1 << pin_struct->pin);

                if (pin_struct->pull_up == PULL_UP) {
                    PORTB |= 1 << pin_struct->pin;
                }
                else if (pin_struct->pull_up == NO_PULL_UP) {
                    PORTB &= ~(1 << pin_struct->pin);
                }
            }

            break;
        }

        case PC:
        {
            if (pin_struct->direction == OUTPUT) {
                DDRC |= 1 << pin_struct->pin;
            }
            else if (pin_struct->direction == INPUT) {
                DDRC &= ~(1 << pin_struct->pin);

                if (pin_struct->pull_up == PULL_UP) {
                    PORTC |= 1 << pin_struct->pin;
                }
                else if (pin_struct->pull_up == NO_PULL_UP) {
                    PORTC &= ~(1 << pin_struct->pin);
                }
            }

            break;
        }

        case PD:
        {
            if (pin_struct->direction == OUTPUT) {
                DDRD |= 1 << pin_struct->pin;
            }
            else if (pin_struct->direction == INPUT) {
                DDRD &= ~(1 << pin_struct->pin);

                if (pin_struct->pull_up == PULL_UP) {
                    PORTD |= 1 << pin_struct->pin;
                }
                else if (pin_struct->pull_up == NO_PULL_UP) {
                    PORTD &= ~(1 << pin_struct->pin);
                }
            }

            break;
        }

        case PE:
        {
            if (pin_struct->direction == OUTPUT) {
                DDRE |= 1 << pin_struct->pin;
            }
            else if (pin_struct->direction == INPUT) {
                DDRE &= ~(1 << pin_struct->pin);

                if (pin_struct->pull_up == PULL_UP) {
                    PORTE |= 1 << pin_struct->pin;
                }
                else if (pin_struct->pull_up == NO_PULL_UP) {
                    PORTE &= ~(1 << pin_struct->pin);
                }
            }

            break;
        }

        case PF:
        {
            if (pin_struct->direction == OUTPUT) {
                DDRF |= 1 << pin_struct->pin;
            }
            else if (pin_struct->direction == INPUT) {
                DDRF &= ~(1 << pin_struct->pin);

                if (pin_struct->pull_up == PULL_UP) {
                    PORTF |= 1 << pin_struct->pin;
                }
                else if (pin_struct->pull_up == NO_PULL_UP) {
                    PORTF &= ~(1 << pin_struct->pin);
                }
            }

            break;
        }
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
