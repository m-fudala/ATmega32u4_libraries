#include "uart.h"

UART uart;

void uart_struct_init(unsigned char baud_rate, UART uart_proto) {
    uart.baud_rate = baud_rate;

    uart.uart_config.character_size =
        uart_proto.uart_config.character_size ?
        uart_proto.uart_config.character_size : BIT_8;
    uart.uart_config.stop_bits =
        uart_proto.uart_config.stop_bits ? uart_proto.uart_config.stop_bits
        : STOP_BIT_1;
    uart.uart_config.parity =
        uart_proto.uart_config.parity ? uart_proto.uart_config.parity
        : NONE;

    uart.uart_bytes_unread = 0;
    uart.uart_status.message_ready = MESSAGE_NOT_READY;

    uart_init();
}

void uart_init() {
    cli();

    switch (uart.baud_rate)
    {
        case BAUD_9600: {
            UBRR1H = 0;
            UBRR1L = 103;

            break;
        }

        case BAUD_19_2K: {
            UBRR1H = 0;
            UBRR1L = 51;

            break;
        }

        case BAUD_38_4K: {
            UBRR1H = 0;
            UBRR1L = 25;

            break;
        }

        case BAUD_76_8K: {
            UBRR1H = 0;
            UBRR1L = 12;

            break;
        }

        case BAUD_250K: {
            UBRR1H = 0;
            UBRR1L = 3;

            break;
        }

        case BAUD_500K: {
            UBRR1H = 0;
            UBRR1L = 1;

            break;
        }

        case BAUD_1M: {
            UBRR1H = 0;
            UBRR1L = 0;

            break;
        }
    }
    
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
    if (uart.uart_status.frame_error) {
        return MESSAGE_FRAME_ERROR;
    } else if (uart.uart_status.data_overrun_error) {
        return MESSAGE_DATA_OVERRUN_ERROR;
    } else if (uart.uart_status.parity_error) {
        return MESSAGE_PARITY_ERROR;
    } else {
        return uart.uart_status.message_ready;
    }
}

ISR(USART1_RX_vect) {
    if (UCSR1A & _BV(FE1)) {
        uart.uart_status.frame_error = 1;
    } else 
    if (UCSR1A & _BV(DOR1)) {
        uart.uart_status.data_overrun_error = 1;
    } else if (UCSR1A & _BV(UPE1)) {
        uart.uart_status.parity_error = 1;
    }

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
