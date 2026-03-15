#ifndef DD_BUTTON_H
#define DD_BUTTON_H

#include <stdint.h>
#include <stdio.h>
#include <Arduino.h>

typedef struct
{
    uint8_t pin;

    int (*readPin)(uint8_t pin);

    FILE stream;
} button_t;

void myButtonSetup(button_t *btn,
                   int (*readPin)(uint8_t pin));

void myButtonArduinoSetup(button_t *btn, uint8_t pin);

#endif // DD_BUTTON_H
