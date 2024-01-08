#include "gpio.h"

int main()
{
    struct Pin pinC6, pinD7;
    pin_init(&pinC6, PC, PC6, OUTPUT, NO_PULL_UP);
    pin_init(&pinD7, PD, PD7, INPUT, PULL_UP);

    unsigned char read_result = 0, write_result = 0;

    while (1) {
        read_result = pin_read(&pinD7);

        write_result = pin_write(&pinC6, !read_result);

        if (write_result) {
            // error handling
        }
    }
    return 0;
}