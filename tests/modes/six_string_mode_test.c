#include "tests.h"
#include "six_string_mode.h"
#include "terminal_write.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 14,
    .freqs = {82.03, 110.352, 146.48, 164.062, 195.8, 220.2, 293.95, 328.11, 391.1, 440.43, 486.816, 586.914, 730.469, 782.715}
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
