#include "terminal_write.h"
#include "six_string_mode.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 3,
    .freqs = {50, 200, 400}
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
