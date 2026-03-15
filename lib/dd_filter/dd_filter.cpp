#include "dd_filter.h"

static int32_t median3(int32_t a, int32_t b, int32_t c)
{
  if (a > b) { int32_t t = a; a = b; b = t; }
  if (b > c) { int32_t t = b; b = c; c = t; }
  if (a > b) { int32_t t = a; a = b; b = t; }
  return b;
}

static int32_t abs_i32(int32_t x) { return x >= 0 ? x : -x; }

void dd_filter_salt_pepper_init(dd_filter_salt_pepper_t *f, int32_t threshold)
{
  if (!f) return;
  f->idx = 0;
  f->filled = 0;
  f->threshold = threshold;
  for (int i = 0; i < 3; i++) f->buf[i] = 0;
}

void dd_filter_salt_pepper_put(dd_filter_salt_pepper_t *f, int32_t value)
{
  if (!f) return;
  f->buf[f->idx] = value;
  f->idx = (f->idx + 1) % 3;
  if (f->filled < 3) f->filled++;
}

int32_t dd_filter_salt_pepper_output(const dd_filter_salt_pepper_t *f)
{
  if (!f || f->filled == 0) return 0;
  int32_t m;
  if (f->filled == 1) m = f->buf[0];
  else if (f->filled == 2) m = (f->buf[0] + f->buf[1]) / 2;
  else m = median3(f->buf[0], f->buf[1], f->buf[2]);
  int32_t last = f->buf[(f->idx + 2) % 3]; /* ultimul pus */
  if (abs_i32(last - m) > f->threshold)
    return m; /* impuls: returnăm mediana */
  return last;
}

void dd_filter_weighted_avg_init(dd_filter_weighted_avg_t *f)
{
  if (!f) return;
  f->idx = 0;
  f->filled = 0;
  for (int i = 0; i < 3; i++) f->buf[i] = 0;
}

void dd_filter_weighted_avg_put(dd_filter_weighted_avg_t *f, int32_t value)
{
  if (!f) return;
  f->buf[f->idx] = value;
  f->idx = (f->idx + 1) % 3;
  if (f->filled < 3) f->filled++;
}

/* Ponderi: 0.25, 0.5, 0.25 pentru [cel mai vechi, mijloc, cel mai nou] */
int32_t dd_filter_weighted_avg_output(const dd_filter_weighted_avg_t *f)
{
  if (!f || f->filled == 0) return 0;
  if (f->filled == 1) return f->buf[0];
  if (f->filled == 2) return (f->buf[0] + f->buf[1]) / 2;
  /* buf[0]=cel mai vechi, buf[1]=mijloc, buf[2]=cel mai nou în ordinea logică */
  int32_t v0 = f->buf[(f->idx) % 3];
  int32_t v1 = f->buf[(f->idx + 1) % 3];
  int32_t v2 = f->buf[(f->idx + 2) % 3];
  return (v0 + 2 * v1 + v2) / 4;
}
