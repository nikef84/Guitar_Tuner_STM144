#include "tests.h"
#include "one_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 6,
    .freqs = {83.496, 166.503, 250.488, 333.007, 585.937, 668.457}
};

static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};


void one_string_mode_test(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    setCurrentString(STRING_4);
    dbgPrintf("Start\r\n");
    oneStringMode(&peaksParams, &stringParams);
    while (true) {
        dbgPrintf("%d    %0.3f\r\n", stringParams.Error, stringParams.oneStringFreq);
        chThdSleepMilliseconds(1000000);
    }
}
