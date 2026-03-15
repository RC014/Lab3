#include "dd_encoder_ky040.h"

void dd_encoder_ky040_init(dd_encoder_ky040_t *enc, uint8_t clk_pin, uint8_t dt_pin, uint8_t sw_pin)
{
  if (!enc) return;
  enc->clk_pin = clk_pin;
  enc->dt_pin  = dt_pin;
  enc->sw_pin  = sw_pin;
  enc->position = 0;
  enc->last_direction = 0;
  enc->button_pressed = false;
  pinMode(enc->clk_pin, INPUT_PULLUP);
  pinMode(enc->dt_pin,  INPUT_PULLUP);
  pinMode(enc->sw_pin,  INPUT_PULLUP);
  enc->last_clk = (uint8_t)digitalRead(enc->clk_pin);
}

void dd_encoder_ky040_update(dd_encoder_ky040_t *enc)
{
  if (!enc) return;

  uint8_t clk = (uint8_t)digitalRead(enc->clk_pin);
  uint8_t dt  = (uint8_t)digitalRead(enc->dt_pin);
  uint8_t sw  = (uint8_t)digitalRead(enc->sw_pin);

  enc->button_pressed = (sw == LOW);  /* PULLUP: apăsat = LOW */
  /* last_direction se actualizează doar la muchie; rămâne +1/-1 până la următoarea rotație */

  /* Muchie pe CLK: determinăm direcția din DT */
  if (clk != enc->last_clk) {
    if (dt != clk) {
      enc->position++;
      enc->last_direction = 1;  /* CW */
    } else {
      enc->position--;
      enc->last_direction = -1; /* CCW */
    }
  }
  enc->last_clk = clk;
}

void dd_encoder_ky040_reset_position(dd_encoder_ky040_t *enc)
{
  if (enc) enc->position = 0;
}
