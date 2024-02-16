/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"

int main()
{
    USBCON = 0;

    uart_start(BAUD_1M, .uart_config.parity = EVEN);

    unsigned char hello[14] = "Hello, world!";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char) - 1);

    while (1) {
        if (check_message_readiness()) {
            unsigned char read_buffer[10] = {' '};

            uart_read(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));

            uart_send(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));
        }
    }

    return 0;
}