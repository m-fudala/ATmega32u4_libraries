/*
    Example of using external interrupt library.
    LED connected to digital pin 6 is toggled through falling edge on pin 7
    (external interrupt 6), which is connected to debounced button. 

    https://github.com/m-fudala
*/

#include "external_interrupt.h"
#include "../gpio_library/gpio.h"

Pin LED;    // initialize Pin struct for an LED as a global variable, in order
            // to be used in interrupt handler

void led_toggle();  // function prototype

int main()
{
    // initialize LED and Button pins
    Pin Button;
    pin_init(&LED, &PORTC, PC6, OUTPUT);
    pin_init(&Button, &PORTE, PE6, INPUT);

    int_init(INT6, led_toggle, FALLING_EDGE);   // set interrupt to trigger on
                                                // falling edge

    int_enable(INT6);   // enable interrupt

    while (1);

    return 0;
}

// function called in interrupt handler
void led_toggle() {
    pin_toggle(&LED);   // toggling the LED pin
}