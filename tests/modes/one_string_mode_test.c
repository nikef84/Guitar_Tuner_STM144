#include "tests.h"
#include "one_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 10,
    .freqs = {78.125, 156.25, 235.839, 312.988, 392.089, 472.167, 551.757, 631.347, 710.449, 791.503}
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
    setCurrentString(STRING_6);
    dbgPrintf("Start\r\n");
    oneStringMode(&peaksParams, &stringParams);
    while (true) {
        dbgPrintf("%d    %0.3f\r\n", stringParams.Error, stringParams.oneStringFreq);
        chThdSleepMilliseconds(1000000);
    }
}
