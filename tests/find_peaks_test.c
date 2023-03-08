#include "findPeaks.h"
#include "terminal_write.h"
#include "signal_recording.h"
#include "power_fft.h"

static peaksAllParams testParam = {
    .indicesOfFreqs = {0},
    .ampOfFreqs = {0},
    .lengthOfArrays = 0,
    .freqs = {0}
};

static uint16_t signal [MAIN_SIGNAL_LENGTH] = {0};
static float spec[SPEC_LENGTH] = {0};

void find_peaks_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    recordMainSignal(signal);
    dbgPrintf("start\r\n");
    fft(spec, signal);
    searchForRequiredPeaks(spec, &testParam);
    dbgPrintf("%d\r\n", testParam.lengthOfArrays);
    while (true) {
        for (uint8_t i = 0; i < testParam.lengthOfArrays; i++){
            dbgPrintf("freq = %0.3f      amp = %0.3f\r\n", testParam.freqs[i], testParam.ampOfFreqs[i]);
        };
        chThdSleepMilliseconds(100000);
    }
}

//static float spec[SPEC_LENGTH] = {0, 0.05, 0.001,  0, 0.002, 0, 0, 0, 0, 0, 0.005, 0.07, 0.001};
//
//void find_peaks_test(void) {
//
//    halInit();
//    chSysInit();
//    debugStreamInit();
//    dbgPrintf("Start\r\n");
//    spec[4000] = 0.01;
//    searchForRequiredPeaks(spec, &testParam);
//    while (true) {
//        dbgPrintf("%f\r\n", SPEC_DF);
//        dbgPrintf("len = %d\r\n", testParam.lengthOfArrays);
//        dbgPrintf("i     f     A\r\n");
//        for (uint8_t i = 0; i < testParam.lengthOfArrays; i++) {
//            dbgPrintf("%d    %0.3f    %0.3f\r\n", testParam.indicesOfFreqs[i], testParam.freqs[i], testParam.ampOfFreqs[i]);
//        }
//        chThdSleepMilliseconds(100000);
//    }
//}
