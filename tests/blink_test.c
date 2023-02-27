#include "common.h"

void blinkTest(void){
  halInit();
  chSysInit();
  while (true) {

     palToggleLine(LINE_LED2);
     chThdSleepMilliseconds(100);
  }
}
