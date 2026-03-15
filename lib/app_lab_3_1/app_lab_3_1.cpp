#include "app_lab_3_1.h"

SemaphoreHandle_t xPrintfMutex = NULL;
SemaphoreHandle_t xStateMutex  = NULL;
app_lab_3_1_signals_t app_signals = { 0 };

void app_lab_3_1_setup(void)
{
  ddSerialStdioSetup();

  app_signals.encoder_position   = 0;
  app_signals.encoder_direction  = 0;
  app_signals.encoder_button    = false;
  app_signals.system_state      = SYS_STATE_ACQUIRING;

  xPrintfMutex = xSemaphoreCreateMutex();
  xStateMutex  = xSemaphoreCreateMutex();

  app_lab_3_1_task_encoder_setup();
  app_lab_3_1_task_display_setup();

  xTaskCreate(app_lab_3_1_task_encoder, "enc", 256, NULL, 1, NULL);
  xTaskCreate(app_lab_3_1_task_display,  "disp", 384, NULL, 1, NULL);

  vTaskStartScheduler();
}

void app_lab_3_1_loop(void)
{
}
