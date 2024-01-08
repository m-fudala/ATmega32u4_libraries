#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

int main()
{
    struct Pin pinC6;
    pin_init(&pinC6, PORTC, PC6, OUTPUT, NO_PULL_UP);

    while (1) {
        pin_write(&pinC6, HIGH);
        _delay_ms(500);
        pin_write(&pinC6, LOW);
        _delay_ms(500);
    }
    return 0;
}