#include "common.h"

void stepperMotorTest(void){
  halInit();
  chSysInit();
  palSetGroupMode(GPIOA, 0x0F, 0, PAL_MODE_OUTPUT_PUSHPULL);
  uint8_t state = 8;
  while (true) {
    palWriteGroup(GPIOA, 0x0F, 0, state);

    if (state == 1) state = 8;
    else state = state >> 1;

    chThdSleepMilliseconds(5);
  }
}
