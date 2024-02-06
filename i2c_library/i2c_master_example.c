#include "i2c.h"
#include <util/delay.h>

int main()
{
    USBCON = 0;

    i2c_master_init(I2C_100000);

    unsigned char hello[14] = "Hello, world!";

    i2c_write((8 << 1), hello, sizeof(hello) / sizeof(unsigned char));

    _delay_ms(200);

    unsigned char counter[] = {'0'};

    while (1) {
        i2c_write((8 << 1), counter, 1);

        ++counter[0];

        if (counter[0] == ('0' + 10)) {
            counter[0] = '0';
        }

        _delay_ms(200);
    }

    return 0;
}