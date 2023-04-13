#include "tests.h"
#include "find_string_freqs.h"
#include "signal_recording.h"
#include "terminal_write.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};

// An array that stores the values of the main signal.
static uint16_t mainSignalBuf[MAIN_SIGNAL_LENGTH] = {0};

// Change branch to "labview_test"!!! And run serial_test_v2.vi
void labview_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    setOperatingMode(SIX_STRING_MODE);
    setCurrentString(0);
    recordMainSignal(mainSignalBuf);
    findStringParams(mainSignalBuf, &stringParams);
    while (true) {
        sdWrite(&SD3, (uint8_t *)&stringParams.oneStringFreq, 4);
        sdWrite(&SD3, (uint8_t *)stringParams.sixStringFreqs, 24);
        chThdSleepMilliseconds(1000);
        sdWrite(&SD3, (uint8_t *)&stringParams.Error, 1);
        chThdSleepMilliseconds(1000000);
    }
}
