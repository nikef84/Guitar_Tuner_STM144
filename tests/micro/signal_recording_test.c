#include "tests.h"
#include "signal_recording.h"
#include "terminal_write.h"

static uint16_t array[MAIN_SIGNAL_LENGTH] = {0};

void signal_recording_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    while (true) {
        recordMainSignal(array);
        dbgPrintf("%d\r\n", array[MAIN_SIGNAL_LENGTH - 1]);
    }

}
