/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"
#include "../gpio_library/gpio.h"

int main()
{
    USBCON = 0;

    uart_init();

    unsigned char hello[14] = "Hello, world!";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char));

    // Pin LED;
    // pin_init(&LED, &PORTC, PC6, OUTPUT);

    while (1) {
        if (message_ready) {
            // pin_write(&LED, HIGH);

            unsigned char read_buffer[10] = {' '};

            uart_read(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));

            uart_send(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));
        }
    }

    return 0;
}