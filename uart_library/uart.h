/*
    Library handling Universal asynchronous receiver-transmitter of the
    ATmega32u4. https://www.microchip.com/en-us/product/atmega32u4

    Author: https://github.com/m-fudala
*/

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define UART_BUFFER_SIZE 32     // size of receive buffer

#define uart_start(BAUD, ...) uart_struct_init((BAUD), (UART){__VA_ARGS__});
                                // macro invoked when uart_start is called
                                // this macro is used to populate UART struct
                                // with mandatory argument of baud rate and
                                // optional arguments of character size, number
                                // of stop bits and parity
                                // defaults are: 8 bit character size, 1 stop
                                // bit and no parity checking

#define UART_DATA_REGISTER_EMPTY (UCSR1A & _BV(UDRE1))  // used in transmitting

enum Baud_rate {    // baud rates calculated for 16 MHz clock, with less
    BAUD_9600,      // than 0.5% error
    BAUD_19_2K,
    BAUD_38_4K,
    BAUD_76_8K,
    BAUD_250K,
    BAUD_500K,
    BAUD_1M,
};

enum Character_size {   // possible character sizes
    BIT_5,
    BIT_6,
    BIT_7,
    BIT_8,
};

enum Stop_bits {        // possible number of stop bits
    STOP_BIT_1,
    STOP_BIT_2
};

enum Parity {           // possible options for parity checking
    NONE,
    EVEN = 2,
    ODD = 3
};

typedef struct UART {    // struct holding configuration for UART
    unsigned char baud_rate;

    struct {
        unsigned char character_size : 3;
        unsigned char stop_bits : 1;
        unsigned char parity : 2;
    } uart_config;

    volatile unsigned char uart_buf[UART_BUFFER_SIZE];
    volatile unsigned char uart_bytes_unread;

    struct {    // status of received message
        volatile unsigned char message_ready : 1;
        volatile unsigned char frame_error : 1;
        volatile unsigned char data_overrun_error : 1;
        volatile unsigned char parity_error : 1;
    } uart_status;
} UART;

/*
    Function initializing struct with UART configuration

    Parameters:
        baud_rate - value selected from Baud_rate enum
        uart_default - struct containing default UART settings, which can be
                       optionally populated with different configuration
                       this struct is handled by uart_start macro
*/

void uart_struct_init(unsigned char baud_rate, UART uart_default);

/*
    Function initializing UART

    Comments:
        is invoked from uart_struct_init function, which in turn is invoked by
        uart_start macro
*/

void uart_init();

/*
    Function sending provided bytes

    Parameters:
        bytes - pointer to buffer with bytes to send
        no_of_bytes - number of bytes to send
*/

void uart_send(unsigned char *bytes, unsigned char no_of_bytes);

/*
    Function reading incoming bytes to given buffer

    Parameters:
        buffer - pointer to buffer to which incoming bytes will be saved
        no_of_bytes - number of bytes to read
*/

void uart_read(unsigned char *buffer, unsigned char no_of_bytes);

enum Message_readiness {    // enum holding possible returns from 
                            // check_message_readiness function
    MESSAGE_READY,
    MESSAGE_NOT_READY,
    MESSAGE_FRAME_ERROR,
    MESSAGE_DATA_OVERRUN_ERROR,
    MESSAGE_PARITY_ERROR
};

/*
    Function checking if properly terminated string can be read

    Returns:
        value from enum Message_readiness
*/

unsigned char check_message_readiness();

#endif