#include "tests.h"
#include "one_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 3,
    .freqs = {200, 150, 400}
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
    oneStringMode(&peaksParams, &stringParams);
    while (true) {
        dbgPrintf("%d    %0.3f\r\n", stringParams.Error, stringParams.oneStringFreq);
        chThdSleepMilliseconds(1000000);
    }
}
