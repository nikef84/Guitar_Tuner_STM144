#include "common.h"
#include "terminal_write.h"


void terminal_write_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    uint16_t num = 0;
    dbgPrintf("Start\r\n");
    while (true) {
        if (num < 10) dbgPrintf("NUM = %f\r\n", SPEC_DF);
        palToggleLine(LINE_LED2);
        num = num + 1;
        chThdSleepMilliseconds(1000);
    }
}
