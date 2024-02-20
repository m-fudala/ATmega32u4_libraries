/*
    Library handling Universal asynchronous receiver-transmitter of the
    ATmega32u4. https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_BUFFER_SIZE 32

#define uart_start(BAUD, ...) uart_struct_init((BAUD), (UART){__VA_ARGS__});

#define UART_DATA_REGISTER_EMPTY (UCSR1A & _BV(UDRE1))

enum Baud_rate {
    BAUD_9600,
    BAUD_19_2K,
    BAUD_38_4K,
    BAUD_76_8K,
    BAUD_250K,
    BAUD_500K,
    BAUD_1M,
};

enum Character_size {
    BIT_5,
    BIT_6,
    BIT_7,
    BIT_8,
};

enum Stop_bits {
    STOP_BIT_1,
    STOP_BIT_2
};

enum Parity {
    NONE,
    EVEN = 2,
    ODD = 3
};

typedef struct
{
    unsigned char baud_rate;

    struct {
        unsigned char character_size : 3;
        unsigned char stop_bits : 1;
        unsigned char parity : 2;
    } uart_config;

    volatile unsigned char uart_buf[UART_BUFFER_SIZE];
    volatile unsigned char uart_bytes_unread;

    struct {
        volatile unsigned char message_ready : 1;
    } uart_status;
} UART;

enum Message_readiness {
    MESSAGE_NOT_READY,
    MESSAGE_READY
};

/*
    Function initializing struct with UART configuration

    Parameters:

    Returns:
*/

void uart_struct_init(unsigned char baud_rate, UART uart_proto);

/*
    Function initializing UART

    Parameters:

    Returns:
*/

void uart_init();

/*
    Function sending provided bytes

    Parameters:
        bytes - pointer to buffer with bytes to send
        no_of_bytes - number of bytes to send

    Returns:
*/

void uart_send(unsigned char *bytes, unsigned char no_of_bytes);

/*
    Function reading incoming bytes to given buffer

    Parameters:
        buffer - pointer to buffer to which incoming bytes will be saved
        no_of_bytes - number of bytes to read

    Returns:
*/

void uart_read(unsigned char *buffer, unsigned char no_of_bytes);

unsigned char check_message_readiness();

#endif