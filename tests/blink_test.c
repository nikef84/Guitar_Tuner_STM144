#include "common.h"

void blink_test(void){
  halInit();
  chSysInit();
  while (true) {

     palToggleLine(LINE_LED2);
     chThdSleepMilliseconds(100);
  }
}
