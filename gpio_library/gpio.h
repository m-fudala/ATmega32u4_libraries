/*
    Library handling General Purpose pins of the ATmega32u4.
    https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

#define PULLUP_GLOBAL_DISABLE MCUCR |= _BV(PUD)     // disable pull-ups
#define PULLUP_GLOBAL_ENABLE MCUCR &= ~_BV(PUD)   // enable pull-ups

enum Pin_direction {    // possible directions for a pin
    OUTPUT,
    INPUT,
    INPUT_PULLUP
};

enum Pin_state {    // possible states for a pin
    LOW,
    HIGH
};

typedef struct Pin {    // struct describing a pin
    unsigned char *port;                // pointer to PORTxn register
    unsigned char *direction_reg;       // pointer to DDRxn register
    unsigned char *pin_reg;             // pointer to PINxn register

    struct {
        unsigned char pin : 3;
        unsigned char direction : 2;
    } config;
} Pin;

enum Init_returns {    // enum holding possible returns of pin_init function
    PIN_INIT_OK,
    PIN_INIT_INVALID_PORT,
    PIN_INIT_INVALID_PIN,
    PIN_INIT_INVALID_DIRECTION
};

/*
    Function initializing a pin

    Parameters:
        pin_struct - pointer to struct of type Pin
        port - pointer to pin's port
        pin - number of the pin
        direction - pin configuration, as described in enum Pin_direction

    Returns:
        value from enum Init_returns
*/

unsigned char pin_init(Pin *pin_struct, volatile unsigned char *port,
                        unsigned char pin, unsigned char direction);


enum Write_returns {    // enum holding possible returns of pin_write function
    PIN_WRITE_OK,
    PIN_WRITE_INVALID_DIRECTION,
    PIN_WRITE_INVALID_STATE
};

/*
    Function writing to pin's output

    Comments:
        Writing only works if pin is configured as output

    Parameters:
        pin_struct - pointer to struct of type Pin
        state - pin's state, as described in enum Pin_state

    Returns:
        value from enum Write_returns
*/

unsigned char pin_write(Pin *pin_struct, unsigned char state);

/*
    Function reading input of a pin

    Comments:
        Pin can be read irregardless of its configuration

    Parameters:
        pin_struct - pointer to struct of type Pin

    Returns:
        value from enum Pin_state
*/

unsigned char pin_read(Pin *pin_struct);

/*
    Function toggling a value in PORTx register

    Parameters:
        pin_struct - pointer to struct of type Pin
*/

void pin_toggle(Pin *pin_struct);

#endif