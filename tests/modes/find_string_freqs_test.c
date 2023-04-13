#include "tests.h"
#include "find_string_freqs.h"
#include "terminal_write.h"



static stringFreqsParams stringParams = {
	.result = {0},
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};


void find_string_freqs_test(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();

    dbgPrintf("Start\r\n");
    while (true) {
        findStringParams(&stringParams);
        dbgPrintf("Error = %d\r\n", stringParams.Error);
        if (MODE == SIX_STRING_MODE) dbgPrintf("Six strings mode\r\n");
        else if (MODE == ONE_STRING_MODE) dbgPrintf("One string mode\r\n");

        for (uint8_t i = 0; i < 6; i++) dbgPrintf("%d     %0.3f\r\n", i + 1, stringParams.result[i]);

        chThdSleepMilliseconds(10000);
    }
}
