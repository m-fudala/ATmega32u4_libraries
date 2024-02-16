#include "uart.h"

void uart_init() {
    cli();

    bytes_unread = 0;
    message_ready = 0;

    UBRR1L = 3;   // 250k baud
        // UMSEL = 0
        // UPM = 0
        // USBS = 0
    UCSR1C |= _BV(UCSZ11) | _BV(UCSZ10);
    UCSR1C &= ~_BV(UCPOL1);

    UCSR1B |= _BV(RXCIE1) | _BV(RXEN1) | _BV(TXEN1);

    sei();
}

void uart_send(unsigned char *bytes, unsigned char no_of_bytes) {
    for (unsigned char byte_no; byte_no < no_of_bytes; ++byte_no) {
        while (!UART_DATA_REGISTER_EMPTY);

        UDR1 = bytes[byte_no];
    }
}

void uart_read(unsigned char *buffer, unsigned char no_of_bytes) {
    for (unsigned char byte_no; byte_no < no_of_bytes; ++byte_no) {
        buffer[byte_no] = buf[byte_no];
    }

    message_ready = 0;
    bytes_unread = 0;
}

unsigned char get_unread_bytes() {
    return bytes_unread;
}

ISR(USART1_RX_vect) {
    if (bytes_unread == UART_BUFFER_SIZE) {
        bytes_unread = 0;
    }

    buf[bytes_unread] = UDR1;

    if (buf[bytes_unread] == '\n') {
        message_ready = 1;
    } else {
        message_ready = 0;
    }

    ++bytes_unread;
}
