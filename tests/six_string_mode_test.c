#include "terminal_write.h"
#include "six_string_mode.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 3,
    .freqs = {100, 150, 400}
};

static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};


void six_string_mode_test(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    functionality_check(&peaksParams, &stringParams);
    while (true) {
        dbgPrintf("%d\r\n", stringParams.Error);
        chThdSleepMilliseconds(1000000);
    }
}
