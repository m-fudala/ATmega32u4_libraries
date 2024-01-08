#include "gpio.h"

int main()
{
    struct Pin LED, Button;
    pin_init(&LED, PC, PC6, OUTPUT, NO_PULL_UP);
    pin_init(&Button, PD, PD7, INPUT, PULL_UP);

    unsigned char read_result = 0, write_result = 0;

    while (1) {
        read_result = pin_read(&Button);

        write_result = pin_write(&LED, !read_result);

        if (write_result) {
            // error handling
        }
    }
    return 0;
}