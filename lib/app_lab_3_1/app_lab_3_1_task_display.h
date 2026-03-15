#ifndef APP_LAB_3_1_TASK_DISPLAY_H
#define APP_LAB_3_1_TASK_DISPLAY_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <stdio.h>

#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../../include/config.h"
#include "app_lab_3_1.h"

void app_lab_3_1_task_display_setup(void);
void app_lab_3_1_task_display(void *pvParameters);

#endif /* APP_LAB_3_1_TASK_DISPLAY_H */
