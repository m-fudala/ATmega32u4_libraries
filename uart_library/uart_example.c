/*
    Example of using UART library.

    https://github.com/m-fudala
*/

#include "uart.h"

int main()
{
    USBCON = 0;     // stop USB interrupts from being triggered

    uart_start(BAUD_250K, .uart_config.parity = EVEN);  // start UART 
                                                        // communication by
                                                        // specifying baud rate
                                                        // and optional
                                                        // settings

    unsigned char hello[16] = "Hello, world!\r\n";

    uart_send(hello, sizeof(hello) / sizeof(unsigned char) - 1);
                                                        // send "Hello, world!"
                                                        // string on start-up

    unsigned char read_buffer[3];
    unsigned char send_ok[5] = "OK\r\n";
    unsigned char send_nok[6] = "NOK\r\n";

    while (1) {
        unsigned char message_ready = check_message_readiness();
                                                        // check if a string
                                                        // terminated with line
                                                        // feed has been
                                                        // received

        // if message has been received
        if (message_ready == MESSAGE_READY) {
            uart_read(read_buffer,
                        sizeof(read_buffer) / sizeof(unsigned char));
                                                        // read receive buffer
                                                        // to one previously
                                                        // defined in main

            // if message is as expected
            if ((read_buffer[0] == 'S') && (read_buffer[1] == 'T') &&
                (read_buffer[2] == 'S')) {
                    uart_send(send_ok,
                        sizeof(send_ok) / sizeof(unsigned char) - 1);
                                                        // send "OK" string

            // if it is not
            } else {
                uart_send(send_nok,
                        sizeof(send_nok) / sizeof(unsigned char) - 1);
                                                        // send "NOK" string
            }
        // in case any receive error is detected
        } else if (message_ready > MESSAGE_NOT_READY) {
            // error handling
        }
    }

    return 0;
}