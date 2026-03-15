#ifndef DD_ENCODER_KY040_H
#define DD_ENCODER_KY040_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>

typedef struct
{
  uint8_t clk_pin;
  uint8_t dt_pin;
  uint8_t sw_pin;
  int32_t position;      /* poziție cumulată (increment/decrement) */
  int8_t last_direction; /* -1 CCW, 0 neschimbat, +1 CW */
  bool button_pressed;   /* SW apăsat (LOW cu PULLUP) */
  uint8_t last_clk;      /* stare anterioară CLK pentru detecție muchie */
} dd_encoder_ky040_t;

void dd_encoder_ky040_init(dd_encoder_ky040_t *enc, uint8_t clk_pin, uint8_t dt_pin, uint8_t sw_pin);

void dd_encoder_ky040_update(dd_encoder_ky040_t *enc);

void dd_encoder_ky040_reset_position(dd_encoder_ky040_t *enc);

#endif /* DD_ENCODER_KY040_H */
