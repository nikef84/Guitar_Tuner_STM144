#include <common.h>

void blink_test(){
  halInit();
  chSysInit();
  while (true) {

     palToggleLine(LINE_LED2);
     chThdSleepMilliseconds(100);
  }
}
