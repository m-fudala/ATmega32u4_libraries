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

void pin_init(struct Pin *pin_struct, unsigned char port, unsigned char pin,
            unsigned char direction, unsigned char pull_up);


enum Write_returns {
    PIN_WRITE_OK,
    PIN_WRITE_INVALID_DIRECTION,
    PIN_WRITE_INVALID_STATE
};

unsigned char pin_write(struct Pin *pin_struct, unsigned char state);


unsigned char pin_read(struct Pin *pin_struct);

void pin_toggle(struct Pin *pin_struct);

void global_pullup_disable();
void global_pullup_enable();

#endif