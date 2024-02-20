#include "external_interrupt.h"

void int0_init(void (*int_function)(void), unsigned char int_level) {
    cli();

    int0_function_pointer = int_function;

    EICRA |= int_level;

    sei();
}

void int0_enable() {
    EIMSK |= _BV(INT0);
}

void int0_disable() {
    EIMSK &= ~_BV(INT0); 
}

ISR (INT0_vect) {
    int0_function_pointer();
}

void int1_init(void (*int_function)(void), unsigned char int_level) {
    cli();

    int1_function_pointer = int_function;

    EICRA |= int_level << 2;

    sei();
}

void int1_enable() {
    EIMSK |= _BV(INT1);
}

void int1_disable() {
    EIMSK &= ~_BV(INT1); 
}

ISR (INT1_vect) {
    int1_function_pointer();
}

void int2_init(void (*int_function)(void), unsigned char int_level) {
    cli();

    int2_function_pointer = int_function;

    EICRA |= int_level << 4;

    sei();
}

void int2_enable() {
    EIMSK |= _BV(INT2);
}

void int2_disable() {
    EIMSK &= ~_BV(INT2); 
}

ISR (INT2_vect) {
    int2_function_pointer();
}

void int3_init(void (*int_function)(void), unsigned char int_level) {
    cli();

    int3_function_pointer = int_function;

    EICRA |= int_level << 6;

    sei();
}

void int3_enable() {
    EIMSK |= _BV(INT3);
}

void int3_disable() {
    EIMSK &= ~_BV(INT3); 
}

ISR (INT3_vect) {
    int3_function_pointer();
}

void int6_init(void (*int_function)(void), unsigned char int_level) {
    cli();

    int6_function_pointer = int_function;

    EICRB |= int_level << 4;

    sei();
}

void int6_enable() {
    EIMSK |= _BV(INT6);
}

void int6_disable() {
    EIMSK &= ~_BV(INT6); 
}

ISR (INT6_vect) {
    int6_function_pointer();
}
