#ifndef APP_LAB_3_2_H
#define APP_LAB_3_2_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../../include/config.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "app_lab_3_2_task_acquisition.h"
#include "app_lab_3_2_task_display.h"

/* Semnale partajate: raw, după filtre, parametru fizic (cu saturare) */
typedef struct {
  int32_t raw_position;       /* poziție brută encoder */
  int32_t after_salt_pepper;  /* după filtru sare și piper */
  int32_t after_weighted_avg; /* după mediere ponderată */
  int32_t physical_value;     /* parametru fizic (saturat în [MIN, MAX]) */
  uint32_t sample_count;
} app_lab_3_2_signals_t;

extern SemaphoreHandle_t xLab32PrintfMutex;
extern SemaphoreHandle_t xLab32StateMutex;
extern app_lab_3_2_signals_t app_lab_3_2_signals;

void app_lab_3_2_setup(void);
void app_lab_3_2_loop(void);

#endif /* APP_LAB_3_2_H */
