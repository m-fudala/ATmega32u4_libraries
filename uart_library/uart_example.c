/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"
#include "../gpio_library/gpio.h"

int main()
{
    USBCON = 0;

    uart_start();

    // uart_start(.uart_config.character_size = BIT_6,
    //             .uart_config.parity = ODD);

    unsigned char hello[14] = "Hello, world!";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char) - 1);

    // Pin LED;
    // pin_init(&LED, &PORTC, PC6, OUTPUT);

    while (1) {
        if (check_message_readiness()) {
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