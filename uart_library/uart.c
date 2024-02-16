#include "uart.h"

UART uart;

void uart_struct_init() {
    uart.uart_config.character_size =
        uart.uart_config.character_size ? uart.uart_config.character_size
        : BIT_8;
    uart.uart_config.stop_bits =
        uart.uart_config.stop_bits ? uart.uart_config.stop_bits
        : STOP_BIT_1;
    uart.uart_config.parity =
        uart.uart_config.parity ? uart.uart_config.parity
        : NONE;

    uart.uart_bytes_unread = 0;
    uart.uart_status.message_ready = MESSAGE_NOT_READY;

    uart_init();
}

void uart_init() {
    cli();

    UBRR1L = 3;   // 250k baud
    
    UCSR1C |= uart.uart_config.character_size << 1;     // character size
    UCSR1C |= uart.uart_config.stop_bits << 2;     // number of stop bits
    UCSR1C |= uart.uart_config.parity << 4;     // parity

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
        buffer[byte_no] = uart.uart_buf[byte_no];
    }

    uart.uart_status.message_ready = MESSAGE_NOT_READY;
    uart.uart_bytes_unread = 0;
}

unsigned char check_message_readiness() {
    return uart.uart_status.message_ready;
}

ISR(USART1_RX_vect) {
    if (uart.uart_bytes_unread == UART_BUFFER_SIZE) {
        uart.uart_bytes_unread = 0;
    }

    uart.uart_buf[uart.uart_bytes_unread] = UDR1;

    if (uart.uart_buf[uart.uart_bytes_unread] == '\n') {
        uart.uart_status.message_ready = MESSAGE_READY;
    } else {
        uart.uart_status.message_ready = MESSAGE_NOT_READY;
    }

    ++uart.uart_bytes_unread;
}
