#include "terminal_write.h"
#include "find_string_freqs.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};


void find_string_freqs_test(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    dbgPrintf("Start\r\n");
    while (true) {
        findStringParams(&stringParams);
        dbgPrintf("\r\n");
        dbgPrintf("error = %d\r\n", stringParams.Error);
        if (MODE == SIX_STRING_MODE) {
            for (uint8_t i = 0; i < 6; i++) dbgPrintf("%d     %0.3f\r\n", (6 - i), stringParams.sixStringFreqs[i]);
        }
        else if (MODE == ONE_STRING_MODE) dbgPrintf("%0.3f\r\n", stringParams.oneStringFreq);

        chThdSleepMilliseconds(10000);
    }
}
