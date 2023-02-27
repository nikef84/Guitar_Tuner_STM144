#include "findPeaks.h"
#include "terminal_write.h"


static peaksAllParams testParam = {
    .indicesOfFreqs = {0},
    .ampOfFreqs = {0},
    .lengthOfArrays = 0,
    .freqs = {0}
};

static float spec[SPEC_LENGTH] = {0, 0.05, 0.001,  0, 0.002, 0, 0, 0, 0, 0, 0.005, 0.07, 0.001};

void find_peaks_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    spec[4000] = 0.01;
    searchForRequiredPeaks(spec, &testParam);
    while (true) {
        dbgPrintf("%f\r\n", SPEC_DF);
//        for (uint8_t i = 0; i < SPEC_LENGTH; i++) dbgPrintf("%f\r\n", spec[i]);
        dbgPrintf("len = %d\r\n", testParam.lengthOfArrays);
        dbgPrintf("i     f     A\r\n");
        for (uint8_t i = 0; i < testParam.lengthOfArrays; i++) {
            dbgPrintf("%d    %0.3f    %0.3f\r\n", testParam.indicesOfFreqs[i], testParam.freqs[i], testParam.ampOfFreqs[i]);
        }
        chThdSleepMilliseconds(100000);
    }
}
