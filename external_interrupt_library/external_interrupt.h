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
    Functions initializing external interrupts

    Parameters:
        int_function - pointer to function that is to be called in ISR
        int_level - value from enum Interrupt_level
*/

void int0_init(void (*int_function)(void), unsigned char int_level);
void int1_init(void (*int_function)(void), unsigned char int_level);
void int2_init(void (*int_function)(void), unsigned char int_level);
void int3_init(void (*int_function)(void), unsigned char int_level);
void int6_init(void (*int_function)(void), unsigned char int_level);

/*
    Functions enabling specified interrupt
*/

void int0_enable();
void int1_enable();
void int2_enable();
void int3_enable();
void int6_enable();

/*
    Functions disabling specified interrupt
*/

void int0_disable();
void int1_disable();
void int2_disable();
void int3_disable();
void int6_disable();

#endif