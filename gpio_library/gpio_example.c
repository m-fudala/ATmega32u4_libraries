/*
    Example of using GPIO library.
    LED connected to digital pin 6 is controlled by button, which pulls pin 5
    to GND.

    https://github.com/m-fudala
*/

#include "gpio.h"

int main()
{
    Pin LED, Button;    // structs holding information for LED and Button pins

    unsigned char init_result = 0;  // returns from pin initialization

    // initializing pin 5 as output and pin 6 as input with pull-up
    init_result += pin_init(&LED, &PORTC, PC6, OUTPUT);
    init_result += pin_init(&Button, &PORTD, PD7, INPUT_PULLUP);

    if (init_result) {
        // error handling
    }

    unsigned char read_result = 0, write_result = 0;    // returns from
                                                        // reading and writing

    while (1) {
        read_result = pin_read(&Button);    // reading current state of the
                                            // button

        write_result = pin_write(&LED, !read_result);   // writing the state
                                                        // to the LED

        if (write_result) {
            // error handling
        }
    }

    return 0;
}