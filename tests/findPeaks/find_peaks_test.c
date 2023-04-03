#include "tests.h"
#include "find_peaks.h"
#include "terminal_write.h"


static peaksAllParams testParam = {
    .ampOfFreqs = {0},
    .lengthOfArrays = 0,
    .freqs = {0}
};

static float spec[SPEC_LENGTH] = {0};

void find_peaks_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    for (uint8_t i = 0; i < 30; i++) spec[1000 + i] = 60 + i;
    for (uint8_t i = 0; i < 30; i++) spec[3000 - i] = 50 - i;
    searchForRequiredPeaks(spec, &testParam);
    while (true) {
        dbgPrintf("Spec df = %f\r\n", SPEC_DF);
        dbgPrintf("len = %d\r\n", testParam.lengthOfArrays);
        dbgPrintf("i     f     A\r\n");
        for (uint8_t i = 0; i < testParam.lengthOfArrays; i++) {
            dbgPrintf("%0.3f    %0.3f\r\n", testParam.freqs[i], testParam.ampOfFreqs[i]);
        }
        chThdSleepMilliseconds(100000);
    }
}
