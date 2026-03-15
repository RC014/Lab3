#ifndef APP_LAB_2_2_TASK_1_H
#define APP_LAB_2_2_TASK_1_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../dd_led/dd_led.h"
#include "../dd_button/dd_button.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"
#include "../../include/config.h"

void app_lab_2_2_task_1_setup();
void task_1(void *pvParameters);

#endif