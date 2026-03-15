#include "app_lab_2_2_task_1.h"

#define ONE_SEC TASK1_ON_TIME_MS
#define TASK_1_REC TASK1_PERIOD_MS // recurenta 10 ms (din config)
#define TASK_1_OFFSET TASK1_START_OFFSET_MS
#define RED_LED_PIN RED_LED

int task1_led_time_cnt = -1; // initializam contorul pentru led
extern SemaphoreHandle_t xSemaphore;

// Instante driver pentru LED si buton
static led_t red_led;
static button_t red_button;

void app_lab_2_2_task_1_setup()
{
  myLedArduinoSetup(&red_led, RED_LED_PIN);
  myButtonArduinoSetup(&red_button, RED_BUTTON_PIN);
}

// Task 1 - LED controlat de buton
// La apasarea butonului aprinde LED-ul timp de 1 s si,
// dupa expirarea timpului, ridica semaforul pentru Task 2.
// Task-ul are recurenta de 10 ms folosind vTaskDelayUntil().
void task_1(void *pvParameters)
{
  TickType_t xLastWakeTime = xTaskGetTickCount();

  vTaskDelay(TASK_1_OFFSET / portTICK_PERIOD_MS);

  while (1)
  {
    bool pressed = false;
    if (red_button.readPin)
    {
      // INPUT_PULLUP: nivel LOW inseamna buton apasat
      pressed = (red_button.readPin(red_button.pin) == LOW);
    }

    // Detectam o noua apasare de buton doar cand LED-ul nu este activ
    if (pressed && task1_led_time_cnt < 0)
    {
      task1_led_time_cnt = ONE_SEC / TASK_1_REC; // numar de pasi de 10 ms pentru 1 s
      ledOn(&red_led);
      printf("\r\nTask1: buton apasat, LED rosu aprins");
    }

    // Asiguram recurenta de 10 ms
    vTaskDelayUntil(&xLastWakeTime, TASK_1_REC / portTICK_PERIOD_MS);

    if (task1_led_time_cnt > 0)
    {
      task1_led_time_cnt--;
      ledOn(&red_led);
    }
    else if (task1_led_time_cnt == 0)
    {
      ledOff(&red_led);
      // Ridicam semaforul pentru a porni Task 2
      xSemaphoreGive(xSemaphore);
      printf("\r\nTask1: semafor ridicat catre Task2\r\n");
      task1_led_time_cnt--;
    }
  }
}