#include "external_interrupt.h"

void int_init(unsigned char interrupt_number, void (*int_function)(void),
        unsigned char int_level) {
    cli();

    switch (interrupt_number)
    {
        case INT0: {
            int0_function_pointer = int_function;

            EICRA |= int_level;

            break;
        }

        case INT1: {
            int1_function_pointer = int_function;

            EICRA |= int_level << 2;

            break;
        }

        case INT2: {
            int2_function_pointer = int_function;

            EICRA |= int_level << 4;

            break;
        }

        case INT3: {
            int3_function_pointer = int_function;

            EICRA |= int_level << 6;

            break;
        }

        case INT6: {
            int6_function_pointer = int_function;

            EICRB |= int_level << 4;

            break;
        }

        default: {
            return;
        }
    }

    sei();
}

void int_enable(unsigned char interrupt_number) {
    EIMSK |= _BV(interrupt_number);
}

void int_disable(unsigned char interrupt_number) {
    EIMSK &= ~_BV(interrupt_number); 
}

ISR (INT0_vect) {
    int0_function_pointer();
}

ISR (INT1_vect) {
    int1_function_pointer();
}

ISR (INT2_vect) {
    int2_function_pointer();
}

ISR (INT3_vect) {
    int3_function_pointer();
}

ISR (INT6_vect) {
    int6_function_pointer();
}
