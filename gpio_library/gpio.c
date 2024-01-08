#include "gpio.h"

void pin_init(struct Pin *pin_struct, unsigned char port, unsigned char pin,
            unsigned char direction, unsigned char pull_up) {
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

unsigned char pin_write(struct Pin *pin_struct, unsigned char state) {
    if (pin_struct->direction != OUTPUT) {
        return PIN_WRITE_INVALID_DIRECTION;
    }
    else if (state > HIGH) {
        return PIN_WRITE_INVALID_STATE;
    }

    switch (pin_struct->port) {
        case PB:
        {
            if (state == HIGH) {
                PORTB |= 1 << pin_struct->pin;
            }
            else if (state == LOW) {
                PORTB &= ~(1 << pin_struct->pin);
            }

            break;
        }

        case PC:
        {
            if (state == HIGH) {
                PORTC |= 1 << pin_struct->pin;
            }
            else if (state == LOW) {
                PORTC &= ~(1 << pin_struct->pin);
            }

            break;
        }

        case PD:
        {
            if (state == HIGH) {
                PORTD |= 1 << pin_struct->pin;
            }
            else if (state == LOW) {
                PORTD &= ~(1 << pin_struct->pin);
            }

            break;
        }

        case PE:
        {
            if (state == HIGH) {
                PORTE |= 1 << pin_struct->pin;
            }
            else if (state == LOW) {
                PORTE &= ~(1 << pin_struct->pin);
            }

            break;
        }

        case PF:
        {
            if (state == HIGH) {
                PORTF |= 1 << pin_struct->pin;
            }
            else if (state == LOW) {
                PORTF &= ~(1 << pin_struct->pin);
            }

            break;
        }
    }

    return PIN_WRITE_OK;
}

unsigned char pin_read(struct Pin *pin_struct) {
    unsigned char pin_read_state = 0;
    unsigned char read_mask = 1 << pin_struct->pin;

    switch (pin_struct->port) {
        case PB:
        {
            return pin_read_state = (PINB & read_mask) >> pin_struct->pin;
        }

        case PC:
        {
            return pin_read_state = (PINC & read_mask) >> pin_struct->pin;
        }

        case PD:
        {
            return pin_read_state = (PIND & read_mask) >> pin_struct->pin;
        }

        case PE:
        {
            return pin_read_state = (PINE & read_mask) >> pin_struct->pin;
        }

        case PF:
        {
            return pin_read_state = (PINF & read_mask) >> pin_struct->pin;
        }
    }
}
