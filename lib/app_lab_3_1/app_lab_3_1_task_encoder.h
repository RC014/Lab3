#ifndef APP_LAB_3_1_TASK_ENCODER_H
#define APP_LAB_3_1_TASK_ENCODER_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "../dd_encoder_ky040/dd_encoder_ky040.h"
#include "../../include/config.h"
#include "app_lab_3_1.h"

void app_lab_3_1_task_encoder_setup(void);
void app_lab_3_1_task_encoder(void *pvParameters);

#endif /* APP_LAB_3_1_TASK_ENCODER_H */
