#include "app_lab_3_1_task_display.h"

static const char* sys_state_str(app_sys_state_t s)
{
  switch (s) {
    case SYS_STATE_IDLE:      return "IDLE";
    case SYS_STATE_ACQUIRING: return "ACQUIRING";
    case SYS_STATE_ERROR:     return "ERROR";
    default:                  return "?";
  }
}

void app_lab_3_1_task_display_setup(void)
{
  (void)0;
}

/**
 * Task afișare: recurență 500 ms; raport pe Serial doar când se modifică
 * poziția encoderului, direcția sau starea butonului SW.
 */
void app_lab_3_1_task_display(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  static int32_t last_pos = 0;
  static int8_t  last_dir = 0;
  static bool    last_btn = false;
  int32_t pos;
  int8_t dir;
  bool btn;
  app_sys_state_t state;
  bool changed;

  vTaskDelay(TASK_DISPLAY_START_OFFSET_MS / portTICK_PERIOD_MS);

  for (;;)
  {
    if (xStateMutex != NULL && xSemaphoreTake(xStateMutex, portMAX_DELAY) == pdTRUE) {
      pos     = app_signals.encoder_position;
      dir     = app_signals.encoder_direction;
      btn     = app_signals.encoder_button;
      state   = app_signals.system_state;
      xSemaphoreGive(xStateMutex);
    } else {
      pos = 0; dir = 0; btn = false; state = SYS_STATE_ERROR;
    }

    changed = (pos != last_pos || dir != last_dir || btn != last_btn);

    if (changed && xPrintfMutex != NULL && xSemaphoreTake(xPrintfMutex, portMAX_DELAY) == pdTRUE) {
      if (xStateMutex != NULL && xSemaphoreTake(xStateMutex, portMAX_DELAY) == pdTRUE) {
        xSemaphoreGive(xStateMutex);
      }
      printf("  Stare sistem:    %s\r\n", sys_state_str(state));
      printf("  Encoder pos:     %ld\r\n", (long)pos);
      printf("  Ultima directie: %d (CW=1, CCW=-1, 0=nicio rotatie)\r\n", (int)dir);
      printf("  Buton SW:        %s\r\n", btn ? "APASAT" : "eliberat");
      printf("---------------------------------------\r\n");
      xSemaphoreGive(xPrintfMutex);
      last_pos = pos;
      last_dir = dir;
      last_btn = btn;
    }

    vTaskDelayUntil(&xLastWakeTime, TASK_DISPLAY_PERIOD_MS / portTICK_PERIOD_MS);
  }
}
