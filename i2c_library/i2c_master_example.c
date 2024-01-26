#include "i2c.h"
#include <util/delay.h>

int main()
{
    struct I2C i2c_master;
    i2c_init(&i2c_master, MASTER, I2C_100000);

    unsigned char hello[14] = "Hello, world!";

    i2c_write_bytes(&i2c_master, (8 << 1), hello,
                    sizeof(hello) / sizeof(unsigned char));

    unsigned char counter = '0';

    while (1) {
        i2c_write(&i2c_master, (8 << 1), counter);

        ++counter;

        if (counter == ('0' + 10)) {
            counter = '0';
        }

        _delay_ms(200);
    }

    return 0;
}