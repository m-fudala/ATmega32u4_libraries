/*
    Library handling external interrupts of the ATmega32u4.
    https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

enum Interrupt_level {  // enum holding possible interrupt levels
    LOW_LEVEL,
    ANY_EDGE,
    FALLING_EDGE,
    RISING_EDGE
};

// pointers to functions to be called in specified interrupt handlers
void (*int0_function_pointer)(void);
void (*int1_function_pointer)(void);
void (*int2_function_pointer)(void);
void (*int3_function_pointer)(void);
void (*int6_function_pointer)(void);

/*
    Function initializing external interrupts

    Parameters:
        interrupt_number - number of interrupt to be controlled
        int_function - pointer to function that is to be called in ISR
        int_level - value from enum Interrupt_level
*/

void int_init(unsigned char interrupt_number, void (*int_function)(void),
        unsigned char int_level);

/*
    Function enabling specified interrupt

    Parameters:
        interrupt_number - number of interrupt to be enabled
*/

void int_enable(unsigned char interrupt_number);

/*
    Function disabling specified interrupt

    Parameters:
        interrupt_number - number of interrupt to be disabled
*/

void int_disable(unsigned char interrupt_number);

#endif