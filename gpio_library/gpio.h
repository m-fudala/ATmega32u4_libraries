#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

enum Ports {
    PB,
    PC,
    PD,
    PE,
    PF
};

enum Pin_direction {
    INPUT,
    OUTPUT
};

enum Pin_state {
    LOW,
    HIGH
};

enum Pull_up_state {
    NO_PULL_UP,
    PULL_UP
};

typedef struct Pin {
    char port;
    char pin;
    char direction;
    char pull_up;
} Pin;

void pin_init(struct Pin *pin_struct, char port, char pin,
            char direction, char pull_up);
void pin_write(struct Pin *pin_struct, char state);

#endif