#include "signal_recording.h"
#include "terminal_write.h"

#define ARRAY_LENGTH        5000
static uint16_t array[ARRAY_LENGTH] = {0};

void signal_recording_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    while (true) {
        recordMainSignal(array, ARRAY_LENGTH);
        dbgPrintf("%d\r\n", array[ARRAY_LENGTH - 1]);
    }

}
