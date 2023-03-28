#include "terminal_write.h"
#include "find_string_freqs.h"

static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};

// Change branch to "labview_test"!!! And run serial_test_v2.vi
void labview_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    findStringParams(&stringParams);
    while (true) {
        sdWrite(&SD3, (uint8_t *)&stringParams.oneStringFreq, 4);
        sdWrite(&SD3, (uint8_t *)stringParams.sixStringFreqs, 24);
        chThdSleepMilliseconds(1000);
        sdWrite(&SD3, (uint8_t *)&stringParams.Error, 1);
        chThdSleepMilliseconds(1000000);
    }
}
