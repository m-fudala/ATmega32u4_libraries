#include "external_interrupt.h"

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
    // int6_function_pointer();
    PINC |= _BV(PC6);
}
