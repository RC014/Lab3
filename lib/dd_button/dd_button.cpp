#include "dd_button.h"

static button_t *active_stdin_button = NULL;

static int button_getchar(FILE *stream)
{
    if (!active_stdin_button || !active_stdin_button->readPin)
    {
        return _FDEV_EOF;
    }

    static bool send_delimiter = false;

    if (send_delimiter)
    {
        send_delimiter = false;
        return ' '; // Return space as delimiter
    }

    send_delimiter = true;
    int pin_state = active_stdin_button->readPin(active_stdin_button->pin);

    if (pin_state == LOW)
    {
        return '1';
    }
    else
    {
        return '0';
    }
}

// Arduino-specific hardware read
static int arduino_readPin(uint8_t pin)
{
    return digitalRead(pin);
}

void myButtonSetup(button_t *btn, int (*readPin)(uint8_t pin))
{
    if (!btn)
        return;

    btn->readPin = readPin;
    btn->stream.get = button_getchar;
    btn->stream.put = NULL; // Read-only
    btn->stream.flags = _FDEV_SETUP_READ;
    btn->stream.udata = NULL;

    active_stdin_button = btn;
    stdin = &btn->stream;
}

void myButtonArduinoSetup(button_t *btn, uint8_t pin)
{
    if (!btn)
        return;

    btn->pin = pin;
    pinMode(pin, INPUT_PULLUP);
    myButtonSetup(btn, arduino_readPin);
    printf("\r\nButton on pin %d configured as stdin stream.\n", pin);
}
