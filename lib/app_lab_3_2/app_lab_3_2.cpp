#include "app_lab_3_2.h"

SemaphoreHandle_t xLab32PrintfMutex = NULL;
SemaphoreHandle_t xLab32StateMutex  = NULL;
app_lab_3_2_signals_t app_lab_3_2_signals = { 0 };

void app_lab_3_2_setup(void)
{
  ddSerialStdioSetup();

  app_lab_3_2_signals.raw_position       = 0;
  app_lab_3_2_signals.after_salt_pepper  = 0;
  app_lab_3_2_signals.after_weighted_avg = 0;
  app_lab_3_2_signals.physical_value     = 0;
  app_lab_3_2_signals.sample_count      = 0;

  xLab32PrintfMutex = xSemaphoreCreateMutex();
  xLab32StateMutex  = xSemaphoreCreateMutex();

  app_lab_3_2_task_acquisition_setup();
  app_lab_3_2_task_display_setup();

  xTaskCreate(app_lab_3_2_task_acquisition, "lab32_acq", 256, NULL, 1, NULL);
  xTaskCreate(app_lab_3_2_task_display,    "lab32_disp", 384, NULL, 1, NULL);

  vTaskStartScheduler();
}

void app_lab_3_2_loop(void)
{
}
