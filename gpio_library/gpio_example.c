#include "gpio.h"

int main()
{
    Pin LED, Button;
    pin_init(&LED, &PORTC, PC6, OUTPUT);
    pin_init(&Button, &PORTD, PD7, INPUT_PULLUP);

    unsigned char read_result = 0, write_result = 0;

    while (1) {
        read_result = pin_read(&Button);

        write_result = pin_write(&LED, !read_result);

        if (write_result) {
            // error handling
        }
    }
    return 0;
}