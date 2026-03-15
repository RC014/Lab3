#include "app_lab_3_2_task_acquisition.h"

static dd_encoder_ky040_t encoder;
static dd_filter_salt_pepper_t salt_pepper;
static dd_filter_weighted_avg_t weighted_avg;

static int32_t clamp_physical(int32_t v)
{
  if (v < LAB32_PHYSICAL_MIN) return LAB32_PHYSICAL_MIN;
  if (v > LAB32_PHYSICAL_MAX) return LAB32_PHYSICAL_MAX;
  return v;
}

void app_lab_3_2_task_acquisition_setup(void)
{
  dd_encoder_ky040_init(&encoder, ENCODER_CLK_PIN, ENCODER_DT_PIN, ENCODER_SW_PIN);
  dd_filter_salt_pepper_init(&salt_pepper, LAB32_IMPULSE_THRESHOLD);
  dd_filter_weighted_avg_init(&weighted_avg);
}

/**
 * Task achiziție + condiționare: recurență cu vTaskDelayUntil(), offset cu vTaskDelay().
 * Flux: citire encoder -> filtru sare și piper -> mediere ponderată -> conversie (identitate)
 *       -> saturare -> actualizare semnale partajate.
 */
void app_lab_3_2_task_acquisition(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  vTaskDelay(TASK_LAB32_ACQ_OFFSET_MS / portTICK_PERIOD_MS);

  for (;;)
  {
    dd_encoder_ky040_update(&encoder);
    int32_t raw = encoder.position;

    dd_filter_salt_pepper_put(&salt_pepper, raw);
    int32_t after_sp = dd_filter_salt_pepper_output(&salt_pepper);

    dd_filter_weighted_avg_put(&weighted_avg, after_sp);
    int32_t after_wa = dd_filter_weighted_avg_output(&weighted_avg);

    /* Conversie: encoder digital -> parametru fizic = poziție (counts); fără ADC/voltage */
    int32_t physical = clamp_physical(after_wa);

    if (xLab32StateMutex != NULL && xSemaphoreTake(xLab32StateMutex, portMAX_DELAY) == pdTRUE) {
      app_lab_3_2_signals.raw_position        = raw;
      app_lab_3_2_signals.after_salt_pepper   = after_sp;
      app_lab_3_2_signals.after_weighted_avg  = after_wa;
      app_lab_3_2_signals.physical_value      = physical;
      app_lab_3_2_signals.sample_count++;
      xSemaphoreGive(xLab32StateMutex);
    }

    vTaskDelayUntil(&xLastWakeTime, TASK_LAB32_ACQ_PERIOD_MS / portTICK_PERIOD_MS);
  }
}
