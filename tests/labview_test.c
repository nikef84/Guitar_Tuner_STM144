#include "terminal_write.h"
#include "find_string_freqs.h"

static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};

void labview_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    findStringParams(&stringParams);
    while (true) {
       for (uint16_t i = 0; i < 6; i++){
           dbgPrintf("%0.3f\r\n", stringParams.sixStringFreqs[i]);
       }
       dbgPrintf("%d\r\n", stringParams.Error);
       chThdSleepMilliseconds(1000000);
    }
}
