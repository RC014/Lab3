#ifndef CONFIG_H
#define CONFIG_H

// Serial communication
#define SERIAL_BAUDRATE 9600

// KY040 Incremental Encoder pins (Arduino digital)
#define ENCODER_CLK_PIN  4   // Clock (A) - quadrature
#define ENCODER_DT_PIN   5   // Data (B) - quadrature
#define ENCODER_SW_PIN   6   // Switch (buton encoder) - INPUT_PULLUP

// FreeRTOS timing (milisecunde)
// Task Encoder - achiziție encoder
#define TASK_ENCODER_PERIOD_MS       10   // recurență achiziție (10 ms)
#define TASK_ENCODER_START_OFFSET_MS 0    // offset față de start

// Task Display - raport periodic
#define TASK_DISPLAY_PERIOD_MS       500  // recurență afișare (500 ms)
#define TASK_DISPLAY_START_OFFSET_MS 100  // offset față de start

// Stare sistem (semnale aplicație)
typedef enum {
  SYS_STATE_IDLE = 0,
  SYS_STATE_ACQUIRING,
  SYS_STATE_ERROR,
  SYS_STATE_COUNT
} app_sys_state_t;

#endif
