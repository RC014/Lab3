#ifndef APP_LAB_2_2_H
#define APP_LAB_2_2_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <queue.h>

#include "../dd_led/dd_led.h"
#include "../dd_button/dd_button.h"
#include "../../include/config.h"
#include "../dd_serial_stdio/dd_serial_stdio.h"

#include "app_lab_2_2_task_1.h"
#include "app_lab_2_2_task_2.h"
#include "app_lab_2_2_task_3.h"

void app_lab_2_2_setup();
void app_lab_2_2_loop();

#endif /* APP_LAB_2_2_H */