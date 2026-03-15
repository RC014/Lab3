#include "app_lab_3_2_task_display.h"

void app_lab_3_2_task_display_setup(void)
{
  (void)0;
}

/**
 * Task afișare: raport pe Serial doar când se modifică vreun parametru al encoderului.
 */
void app_lab_3_2_task_display(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();
  static int32_t last_raw = 0, last_after_sp = 0, last_after_wa = 0, last_physical = 0;
  int32_t raw, after_sp, after_wa, physical;
  uint32_t sample_count;
  bool changed;

  vTaskDelay(TASK_LAB32_DISPLAY_OFFSET_MS / portTICK_PERIOD_MS);

  for (;;)
  {
    if (xLab32StateMutex != NULL && xSemaphoreTake(xLab32StateMutex, portMAX_DELAY) == pdTRUE) {
      raw          = app_lab_3_2_signals.raw_position;
      after_sp     = app_lab_3_2_signals.after_salt_pepper;
      after_wa     = app_lab_3_2_signals.after_weighted_avg;
      physical     = app_lab_3_2_signals.physical_value;
      sample_count = app_lab_3_2_signals.sample_count;
      xSemaphoreGive(xLab32StateMutex);
    } else {
      raw = after_sp = after_wa = physical = 0;
      sample_count = 0;
    }

    changed = (raw != last_raw || after_sp != last_after_sp ||
               after_wa != last_after_wa || physical != last_physical);

    if (changed && xLab32PrintfMutex != NULL && xSemaphoreTake(xLab32PrintfMutex, portMAX_DELAY) == pdTRUE) {
      printf("  Raw (encoder):     %ld\r\n", (long)raw);
      printf("  Dupa sare-piper:   %ld\r\n", (long)after_sp);
      printf("  Dupa med. ponder.: %ld\r\n", (long)after_wa);
      printf("  Parametru fizic:   %ld [saturat %d..%d]\r\n",
             (long)physical, LAB32_PHYSICAL_MIN, LAB32_PHYSICAL_MAX);
      printf("  Nr. esantioane:    %lu\r\n", (unsigned long)sample_count);
      printf("-------------------------------------\r\n");
      xSemaphoreGive(xLab32PrintfMutex);
      last_raw      = raw;
      last_after_sp = after_sp;
      last_after_wa = after_wa;
      last_physical = physical;
    }

    vTaskDelayUntil(&xLastWakeTime, TASK_LAB32_DISPLAY_PERIOD_MS / portTICK_PERIOD_MS);
  }
}
