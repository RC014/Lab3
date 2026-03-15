#ifndef APP_LAB_3_2_TASK_ACQUISITION_H
#define APP_LAB_3_2_TASK_ACQUISITION_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

#include "../dd_encoder_ky040/dd_encoder_ky040.h"
#include "../dd_filter/dd_filter.h"
#include "../../include/config.h"
#include "app_lab_3_2.h"

void app_lab_3_2_task_acquisition_setup(void);
void app_lab_3_2_task_acquisition(void *pvParameters);

#endif /* APP_LAB_3_2_TASK_ACQUISITION_H */
