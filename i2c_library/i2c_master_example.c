#include "i2c.h"
#include <util/delay.h>

int main()
{
    struct I2C i2c_master;
    i2c_init(&i2c_master, MASTER, I2C_100000);

    while (1) {
        i2c_write(&i2c_master, (8 << 1), 123);

        _delay_ms(200);
    }

    return 0;
}