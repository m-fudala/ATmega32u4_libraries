/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"

int main()
{
    USBCON = 0;

    uart_start(BAUD_250K, .uart_config.parity = EVEN);

    unsigned char hello[16] = "Hello, world!\r\n";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char) - 1);

    unsigned char read_buffer[3];
    unsigned char send_ok[5] = "OK\r\n";
    unsigned char send_nok[6] = "NOK\r\n";

    while (1) {
        if (check_message_readiness()) {
            uart_read(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));

            if ((read_buffer[0] == 'S') && (read_buffer[1] == 'T') &&
                (read_buffer[2] == 'S')) {
                    uart_send(send_ok,
                        sizeof(send_ok) / sizeof(unsigned char) - 1);
            } else {
                uart_send(send_nok,
                        sizeof(send_nok) / sizeof(unsigned char) - 1);
            }
        }
    }

    return 0;
}