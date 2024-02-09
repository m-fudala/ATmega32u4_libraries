#include "i2c.h"
#include <util/delay.h>

int main()
{
    USBCON = 0;

    i2c_master_init(I2C_100000);

    unsigned char buffer[6];

    while (1) {
        i2c_write((8 << 1), buffer, sizeof(buffer) / sizeof(unsigned char));

        _delay_ms(200);
    }

    return 0;
}