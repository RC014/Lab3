#include "app_lab_2_2_task_3.h"

#define TASK_3_REC TASK3_PERIOD_MS
#define TASK_3_OFFSET TASK3_START_OFFSET_MS
// Task 3 - Asincron
// La fiecare 200 ms citeste coada si afiseaza octetii cititi in terminal (stdio).
// La detectarea unui octet 0, trece pe un rand nou.
extern QueueHandle_t xQueue;

void app_lab_2_2_task_3_setup()
{
}

void task_3(void *pvParameters)
{
  vTaskDelay(TASK_3_OFFSET / portTICK_PERIOD_MS);
  while (1)
  {
    int data; // buffer in care punem datele primite
    while (xQueueReceive(xQueue, &data, TASK_3_REC / portTICK_PERIOD_MS) == pdTRUE)
    {
      if (data == 0) // daca am primit octetul 0, trecem pe un rand nou
      {
        printf("\r\n");
      }
      else
      {
        printf("%d,", data); // afisam octetul citit
      }
    }
  }
}
