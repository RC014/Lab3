#include "app_lab_2_2_task_2.h"

#define GREEN_LED_PIN GREEN_LED
#define TASK_2_REC TASK2_BYTE_PERIOD_MS
#define TASK_2_OFFSET TASK2_START_OFFSET_MS

// Task 2 - Sincron
// Asteapta ridicarea semaforului de la Task 1, mareste variabila N (N = N + 1)
// si trimite in coada o secventa de N octeti (1,2,3,..,N) la fiecare 50 ms.
// Apoi controleaza LED-ul verde care clipeste de N ori (ON — 300 ms, OFF — 500 ms).

int task_N_cnt = 0;
static led_t green_led;
extern SemaphoreHandle_t xSemaphore;
extern QueueHandle_t xQueue;
void app_lab_2_2_task_2_setup()
{
  myLedArduinoSetup(&green_led, GREEN_LED_PIN);
}
void task_2(void *pvParameters)
{
  vTaskDelay(TASK_2_OFFSET / portTICK_PERIOD_MS);
  while (1)
  {

    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
    {
      printf("\r\nTask2: semafor primit de la Task1");
      task_N_cnt++;

      for (int i = 0; i < task_N_cnt; i++)
      {
        xQueueSend(xQueue, &i, portMAX_DELAY);
        vTaskDelay(TASK_2_REC / portTICK_PERIOD_MS);
      }

      {
        int terminator = 0;
        xQueueSend(xQueue, &terminator, portMAX_DELAY);
      }
      // printf("\r\nTask2: au fost trimisi in coada %d octeti", task_N_cnt + 1);
      printf("\r\nTask2: LED-ul verde clipeste");
      for (int i = 0; i < task_N_cnt; i++)
      {
        ledOn(&green_led);
        vTaskDelay(TASK2_LED_ON_MS / portTICK_PERIOD_MS);
        ledOff(&green_led);
        vTaskDelay(TASK2_LED_OFF_MS / portTICK_PERIOD_MS);
      }
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
