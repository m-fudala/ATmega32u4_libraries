/*
    Example of using external interrupt library.
    LED connected to digital pin 6 is toggled through falling edge on pin 7
    (external interrupt 6), which is connected to debounced button. 

    https://github.com/m-fudala
*/

#include "external_interrupt.h"
#include "../gpio_library/gpio.h"

Pin LED;

void int6_interrupt_handler();

int main()
{
    Pin Button;
    pin_init(&LED, &PORTC, PC6, OUTPUT);
    pin_init(&Button, &PORTE, PE6, INPUT);

    int_init(INT6, int6_interrupt_handler, FALLING_EDGE);
    int_enable(INT6);

    while (1);

    return 0;
}

void int6_interrupt_handler() {
    pin_toggle(&LED);
}