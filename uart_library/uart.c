#include "uart.h"

void uart_init() {
    UBRR1L = 103;   // 9600 baud
        // UMSEL = 0
        // UPM = 0
        // USBS = 0
    UCSR1C |= _BV(UCSZ11) | _BV(UCSZ10);
    UCSR1C &= ~_BV(UCPOL1);
}

void uart_send(unsigned char *bytes, unsigned char no_of_bytes) {
    UCSR1B &= _BV(RXEN1);   // disable RX
    UCSR1B |= _BV(TXEN1);   // enable TX

    for (unsigned char byte_no; byte_no < no_of_bytes; ++byte_no) {
        while (!UART_DATA_REGISTER_EMPTY);

        UDR1 = bytes[byte_no];
    }
}
