#ifndef DD_FILTER_H
#define DD_FILTER_H

#include <stdint.h>

/**
 * Filtru digital "sare și piper" (eliminare zgomot impulsiv).
 * Folosește o fereastră de 3 eșantioane; dacă diferența |x_new - median| > threshold,
 * consideră impuls și returnează median, altfel returnează x_new.
 */
typedef struct {
  int32_t buf[3];   /* circular buffer: cele mai recente 3 eșantioane */
  uint8_t idx;      /* index pentru scriere */
  uint8_t filled;   /* număr de eșantioane valide (1..3) */
  int32_t threshold;
} dd_filter_salt_pepper_t;

void dd_filter_salt_pepper_init(dd_filter_salt_pepper_t *f, int32_t threshold);
void dd_filter_salt_pepper_put(dd_filter_salt_pepper_t *f, int32_t value);
int32_t dd_filter_salt_pepper_output(const dd_filter_salt_pepper_t *f);

/**
 * Filtru digital de mediere ponderată (3 eșantioane: 0.25, 0.5, 0.25).
 * Netezire suplimentară după filtrarea impulsurilor.
 */
typedef struct {
  int32_t buf[3];
  uint8_t idx;
  uint8_t filled;
} dd_filter_weighted_avg_t;

void dd_filter_weighted_avg_init(dd_filter_weighted_avg_t *f);
void dd_filter_weighted_avg_put(dd_filter_weighted_avg_t *f, int32_t value);
int32_t dd_filter_weighted_avg_output(const dd_filter_weighted_avg_t *f);

#endif /* DD_FILTER_H */
