#include "tests.h"
#include "one_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 6,
    .freqs = {140.136, 280.761, 421.386, 562.011, 702.636, 736.328}
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
