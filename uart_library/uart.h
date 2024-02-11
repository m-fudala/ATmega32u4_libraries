/*
    Library handling Universal asynchronous receiver-transmitter of the
    ATmega32u4. https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define UART_DATA_REGISTER_EMPTY (UCSR1A & _BV(UDRE1))
#define UART_INCOMING_BYTES_PRESENT (UCSR1A & _BV(RXC1))

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

    Returns:
*/

void uart_read();

#endif