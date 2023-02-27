#include "common.h"

void stepperMotorTest(void){
  halInit();
  chSysInit();
  palSetGroupMode(GPIOD, 0xF0, 0, PAL_MODE_OUTPUT_PUSHPULL);
  uint8_t state = 128;
  while (true) {
    palWritePort(GPIOD, state);

    if (state == 16) state = 128;
    else state = state >> 1;

    chThdSleepMilliseconds(100);
  }
}
