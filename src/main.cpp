#include <Arduino.h>
#include "../include/config.h"

#if ACTIVE_APP_LAB == 2
#include "../lib/app_lab_3_2/app_lab_3_2.h"
#else
#include "../lib/app_lab_3_1/app_lab_3_1.h"
#endif

void setup(void)
{
#if ACTIVE_APP_LAB == 2
  app_lab_3_2_setup();
#else
  app_lab_3_1_setup();
#endif
}

void loop(void)
{
#if ACTIVE_APP_LAB == 2
  app_lab_3_2_loop();
#else
  app_lab_3_1_loop();
#endif
}
