#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>

#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1
#define NO_PULL_UP 0
#define PULL_UP 1

typedef struct Pin {
    char port;
    char pin;
    char direction;
    char pull_up;
} Pin;

void pin_init(struct Pin *pin_struct, char port, char pin,
            char direction, char pull_up);
void pin_write(struct Pin *pin_struct, char state);

#endif