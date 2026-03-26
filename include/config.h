#ifndef CONFIG_H
#define CONFIG_H

#define ACTIVE_APP_LAB 2

#define SERIAL_BAUDRATE 9600

#define ENCODER_CLK_PIN  4   // Clock (A) - quadrature
#define ENCODER_DT_PIN   5   // Data (B) - quadrature
#define ENCODER_SW_PIN   6   // Switch (buton encoder) - INPUT_PULLUP

// FreeRTOS timing (milisecunde)
#define TASK_ENCODER_PERIOD_MS       10   // recurenta (10 ms)
#define TASK_ENCODER_START_OFFSET_MS 0    // offset fata de start

// Task Display - raport periodic
#define TASK_DISPLAY_PERIOD_MS       500  // recurenta afisare (500 ms)
#define TASK_DISPLAY_START_OFFSET_MS 100  // offset fata de start

// Stare sistem (semnale aplicatie)
typedef enum {
  SYS_STATE_IDLE = 0,
  SYS_STATE_ACQUIRING,
  SYS_STATE_ERROR,
  SYS_STATE_COUNT
} app_sys_state_t;

// ---------- Lab 3.2: Condiționare semnal ----------
#define TASK_LAB32_ACQ_PERIOD_MS       20   // recurență achiziție + condiționare
#define TASK_LAB32_ACQ_OFFSET_MS       0
#define TASK_LAB32_DISPLAY_PERIOD_MS   500
#define TASK_LAB32_DISPLAY_OFFSET_MS   50

// Filtru "sare și piper": prag pentru considerare impuls (diferență față de mediana ferestrei)
#define LAB32_IMPULSE_THRESHOLD        10
// Filtru mediere ponderată: ponderi pentru 3 eșantioane [x[n-2], x[n-1], x[n]] -> 0.25, 0.5, 0.25
// Conversie: encoder digital -> parametru fizic = poziție (counts); saturare în interval valid
#define LAB32_PHYSICAL_MIN            -10000
#define LAB32_PHYSICAL_MAX             10000

#endif
