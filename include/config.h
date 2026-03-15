#ifndef CONFIG_H
#define CONFIG_H

// Serial communication
#define SERIAL_BAUDRATE 9600

// LED Pins (Arduino digital pins)
#define RED_LED    3   // LED roșu (Task 1)
#define GREEN_LED  2   // LED verde (Task 2)

// Button Pins
#define RED_BUTTON_PIN   8   // Buton pentru Task 1 (INPUT_PULLUP recomandat)

// FreeRTOS timing (în milisecunde)
// Task 1 - Button Led
#define TASK1_PERIOD_MS       10    // recurență Task 1 (10 ms)
#define TASK1_ON_TIME_MS      1000  // timp LED roșu aprins după apăsare (1 s)
#define TASK1_START_OFFSET_MS 0

// Task 2 - Sincron (N, trimitere în coadă, clipire LED verde)
#define TASK2_BYTE_PERIOD_MS   50   // interval între octeții trimiși în coadă
#define TASK2_START_OFFSET_MS  50
#define TASK2_LED_ON_MS        300
#define TASK2_LED_OFF_MS       500

// Task 3 - Asincron (citire coadă și afișare)
#define TASK3_PERIOD_MS        200
#define TASK3_START_OFFSET_MS  100

// Coada dintre Task 2 și Task 3
#define APP_LAB_2_2_QUEUE_LENGTH  100   // număr de elemente în coadă
#define APP_LAB_2_2_QUEUE_ITEM_SZ sizeof(uint8_t) // tipul de date din coadă

enum ledState{
    LED_OFF = 0,
    LED_ON,
    LED_TOGGLE
};

#endif