#include "app_lab_2_2.h"

SemaphoreHandle_t xSemaphore = NULL; // Binary semaphore between Task 1 și Task 2
QueueHandle_t xQueue = NULL;         // Coada pentru octeții trimiși între Task 2 și Task 3
SemaphoreHandle_t xPrintfMutex = NULL;

void app_lab_2_2_setup()
{
  ddSerialStdioSetup();

  app_lab_2_2_task_1_setup();
  app_lab_2_2_task_2_setup();
  app_lab_2_2_task_3_setup();

  // Semafoare și coadă
  xSemaphore = xSemaphoreCreateBinary();                                      // semafor binar
  xQueue = xQueueCreate(APP_LAB_2_2_QUEUE_LENGTH, APP_LAB_2_2_QUEUE_ITEM_SZ); // coadă de octeți
  xPrintfMutex = xSemaphoreCreateMutex();

  xTaskCreate(task_1, "\r\nTask 1", 1000, NULL, 1, NULL);
  xTaskCreate(task_2, "\r\nTask 2", 1000, NULL, 1, NULL);
  xTaskCreate(task_3, "\r\nTask 3", 1000, NULL, 1, NULL);

  vTaskStartScheduler();
}

void app_lab_2_2_loop()
{
}