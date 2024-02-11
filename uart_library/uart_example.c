/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"

int main()
{
    uart_init();

    unsigned char hello[14] = "Hello, world!";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char));  

    while (1) {
        // if (UART_INCOMING_BYTES_PRESENT) {

        // }
    }

    return 0;
}