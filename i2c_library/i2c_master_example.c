#include "i2c.h"
#include <util/delay.h>
// #include "../gpio_library/gpio.h"

int main()
{
    USBCON = 0;

    // Pin LED;
    // pin_init(&LED, PC, PC6, OUTPUT, NO_PULL_UP);
    // pin_write(&LED, HIGH);
    // _delay_ms(500);
    // pin_write(&LED, LOW);

    // struct I2C i2c_master;
    i2c_master_init(I2C_100000);

    // unsigned char hello[14] = "Hello, world!";

    // i2c_write_bytes(&i2c_master, (8 << 1), hello,
    //                 sizeof(hello) / sizeof(unsigned char));

    unsigned char counter = '0';

    while (1) {
        i2c_write((8 << 1), counter);

        ++counter;

        if (counter == ('0' + 10)) {
            counter = '0';
        }

        _delay_ms(200);
    }

    return 0;
}