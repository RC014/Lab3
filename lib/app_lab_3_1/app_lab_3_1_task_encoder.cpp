#include "app_lab_3_1_task_encoder.h"

static dd_encoder_ky040_t encoder;

void app_lab_3_1_task_encoder_setup(void)
{
  dd_encoder_ky040_init(&encoder, ENCODER_CLK_PIN, ENCODER_DT_PIN, ENCODER_SW_PIN);
}

/**
 * Task achiziție encoder: recurență prestabilită cu vTaskDelayUntil(),
 * offset cu vTaskDelay(). Actualizează semnalele partajate (position, direction, button).
 */
void app_lab_3_1_task_encoder(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  vTaskDelay(TASK_ENCODER_START_OFFSET_MS / portTICK_PERIOD_MS);

  for (;;)
  {
    dd_encoder_ky040_update(&encoder);

    if (xStateMutex != NULL && xSemaphoreTake(xStateMutex, portMAX_DELAY) == pdTRUE) {
      app_signals.encoder_position  = encoder.position;
      app_signals.encoder_direction = encoder.last_direction;
      app_signals.encoder_button    = encoder.button_pressed;
      app_signals.system_state      = SYS_STATE_ACQUIRING;
      xSemaphoreGive(xStateMutex);
    }

    vTaskDelayUntil(&xLastWakeTime, TASK_ENCODER_PERIOD_MS / portTICK_PERIOD_MS);
  }
}
