#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

enum Ports {    // enum holding port descriptions
    PB,
    PC,
    PD,
    PE,
    PF
};

enum Pin_direction {    // possible directions for a pin
    INPUT,
    OUTPUT
};

enum Pin_state {    // possible states for a pin
    LOW,
    HIGH
};

enum Pull_up_state {    // possible states of a pull-up
    NO_PULL_UP,
    PULL_UP
};

typedef struct Pin {    // struct describing a pin
    char port;
    char pin;
    char direction;
    char pull_up;
} Pin;

// function initializing a pin
void pin_init(struct Pin *pin_struct, unsigned char port, unsigned char pin,
            unsigned char direction, unsigned char pull_up);


enum Write_returns {    // enum holding possible returns of pin_write function
    PIN_WRITE_OK,
    PIN_WRITE_INVALID_DIRECTION,
    PIN_WRITE_INVALID_STATE
};

// function writing pin's output
unsigned char pin_write(struct Pin *pin_struct, unsigned char state);


// function reading input of a pin
unsigned char pin_read(struct Pin *pin_struct);

// function toggling a value in PORTx register
void pin_toggle(struct Pin *pin_struct);

// function enabling/disabling pull-ups globally
void global_pullup_disable();
void global_pullup_enable();

#endif