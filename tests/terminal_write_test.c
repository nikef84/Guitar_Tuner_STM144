#include "common.h"
#include "terminal_write.h"


void terminalWriteTest(void){
    halInit();
    chSysInit();
    debugStreamInit();
    uint16_t num = 0;
    while (true) {
        if (num < 10) dbgPrintf("NUM = %d\r\n", num);
        palToggleLine(LINE_LED2);
        num = num + 1;
        chThdSleepMilliseconds(1000);
    }
}
