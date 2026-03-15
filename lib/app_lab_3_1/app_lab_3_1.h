#ifndef APP_LAB_3_1_H
#define APP_LAB_3_1_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../../include/config.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "app_lab_3_1_task_encoder.h"
#include "app_lab_3_1_task_display.h"

/* Semnale / stare partajată între task-uri (protejată de xStateMutex) */
typedef struct {
  int32_t         encoder_position;
  int8_t          encoder_direction;   /* -1, 0, +1 */
  bool            encoder_button;       /* SW apăsat */
  app_sys_state_t system_state;
} app_lab_3_1_signals_t;

extern SemaphoreHandle_t xPrintfMutex;
extern SemaphoreHandle_t xStateMutex;
extern app_lab_3_1_signals_t app_signals;

void app_lab_3_1_setup(void);
void app_lab_3_1_loop(void);

#endif /* APP_LAB_3_1_H */
