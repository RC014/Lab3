#include "dd_led.h"

// Functii helper statice pentru platforma Arduino
static void arduino_setOutput(uint8_t pin, uint8_t state)
{
    if (state)
    {
        pinMode(pin, OUTPUT);
    }
}
static void arduino_setValue(uint8_t pin, uint8_t state)
{
    digitalWrite(pin, state);
}
static void arduino_toggle(uint8_t pin)
{
    digitalWrite(pin, !digitalRead(pin));
}

void myLedSetup(led_t *led,
                void (*setOutput)(uint8_t pin, uint8_t state),
                void (*setValue)(uint8_t pin, uint8_t state),
                void (*toggle)(uint8_t pin))
{
    if (!led)
        return;

    led->setOutput = setOutput;
    led->setValue = setValue;
    led->toggle = toggle;

    if (led->setOutput)
    {
        led->setOutput(led->pin, DD_LED_OUTPUT);
    }

    if (led->setValue)
    {
        led->setValue(led->pin, LED_OFF);
    }
}

void myLedArduinoSetup(led_t *led, uint8_t pin)
{
    if (!led)
        return;
    led->pin = pin;
    myLedSetup(led, arduino_setOutput, arduino_setValue, arduino_toggle);
}

void ledOn(led_t *led)
{
    if (led && led->setValue)
    {
        led->setValue(led->pin, LED_ON);
    }
}

void ledOff(led_t *led)
{
    if (led && led->setValue)
    {
        led->setValue(led->pin, LED_OFF);
    }
}

void ledToggle(led_t *led)
{
    if (led && led->toggle)
    {
        led->toggle(led->pin);
    }
}
