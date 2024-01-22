#include "i2c.h"

int main()
{
    struct I2C i2c_master;
    i2c_init(&i2c_master, MASTER, I2C_100000);

    while (1) {
        
    }
    return 0;
}