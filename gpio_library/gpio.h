#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

#define PIN_MASK 0b111

enum Pin_direction {    // possible directions for a pin
    INPUT,
    OUTPUT,
    INPUT_PULLUP
};

enum Pin_state {    // possible states for a pin
    LOW,
    HIGH
};

typedef struct Pin {    // struct describing a pin
    unsigned char *port;
    unsigned char *direction_reg;
    unsigned char *pin_reg;
    unsigned char pin_and_direction;
} Pin;

enum Init_returns {
    PIN_INIT_OK,
    PIN_INIT_INVALID_PORT,
    PIN_INIT_INVALID_PIN,
    PIN_INIT_INVALID_DIRECTION
};

// function initializing a pin
unsigned char pin_init(struct Pin *pin_struct, volatile unsigned char *port,
                        unsigned char pin, unsigned char direction);


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