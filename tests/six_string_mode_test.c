#include "terminal_write.h"
#include "six_string_mode.h"

static peaksAllParams peaksParams = {
    .lengthOfArrays = 27,
    .freqs = {82.5, 109.8, 131.8, 164.8, 198.9, 219.9, 248.3, 264.4, 273.4, 396.24, 528.32, 546.63, 593.5, 610.6, 779, 791.7, 819.8, 877.2, 884, 891.6, 898.9, 906.7, 915.8, 924.6, 932.8, 989.501, 998.5}
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
