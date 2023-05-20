#include "tests.h"
#include "six_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 12,
    .freqs = {80.566, 107.421, 161.132, 196.289, 214.843, 236.816, 291.992, 390.136, 437.5, 585.449, 668.457, 709.472}
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
    dbgPrintf("Start\r\n");
    sixStringMode(&peaksParams, &stringParams);
    while (true) {
        dbgPrintf("error = %d\r\n", stringParams.Error);
        for (uint8_t i = 0; i < 6; i++) dbgPrintf("%0.1f\r\n", stringParams.sixStringFreqs[i]);
        chThdSleepMilliseconds(100000);
    }
}
