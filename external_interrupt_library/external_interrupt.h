/*
    Library handling external interrupts of the ATmega32u4.
    https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef EXTERNAL_INTERRUPT_H_
#define EXTERNAL_INTERRUPT_H_

#include <avr/io.h>
#include <avr/interrupt.h>

enum Interrupt_level {
    LOW_LEVEL,
    ANY_EDGE,
    FALLING_EDGE,
    RISING_EDGE
};

void (*int6_function_pointer)(void);

void int6_init(void (*int_function)(void), unsigned char int_level);

void int6_enable();

void int6_disable();

#endif