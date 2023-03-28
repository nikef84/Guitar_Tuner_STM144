#include "common.h"
#include "terminal_write.h"


void terminal_write_test(void){
    halInit();
    chSysInit();
    debugStreamInit();
    uint16_t num = 0;
    dbgPrintf("Start\r\n");
    while (true) {
        if (num < 100) dbgPrintf("NUM = %d\r\n", num);
        palToggleLine(LINE_LED2);
        num = num + 1;
        chThdSleepMilliseconds(100000);
    }
}
