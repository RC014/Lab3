#ifndef APP_LAB_2_2_TASK_3_H
#define APP_LAB_2_2_TASK_3_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../../include/config.h"

void app_lab_2_2_task_3_setup();
void task_3(void *pvParameters);
#endif