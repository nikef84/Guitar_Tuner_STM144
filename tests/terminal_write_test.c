#include "common.h"
#include "terminal_write.h"

//static uint8_t index = 0;
//
//void write1(uint8_t *index){
//    *index = 5;
//}
//void write(uint8_t *index){
//    write1(index);
//}
void terminalWriteTest(void){
    halInit();
    chSysInit();
    debugStreamInit();
    uint16_t num = 0;
    dbgPrintf("Start\r\n");
//    write(&index);
    while (true) {
        if (num < 10) dbgPrintf("NUM = %f\r\n", SPEC_DF);
        palToggleLine(LINE_LED2);
        num = num + 1;
        chThdSleepMilliseconds(1000);
    }
}
