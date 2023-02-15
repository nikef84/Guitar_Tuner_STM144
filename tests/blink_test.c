#include "common.h"

void blinkTest(){
  halInit();
  chSysInit();
  while (true) {

     palToggleLine(LINE_LED2);
     chThdSleepMilliseconds(100);
  }
}
