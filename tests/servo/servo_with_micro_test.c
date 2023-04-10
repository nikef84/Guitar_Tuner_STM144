#include "servo_control.h"
#include "find_string_freqs.h"
#include "terminal_write.h"
#include "tests.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0},
	.result = {0}
};


void servo_control_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
	dbgPrintf("Start\r\n");
	adcSimpleInit();
	servoInit();
    while (true) {
        findStringParams(&stringParams);
        dbgPrintf("Error = %d\r\n", stringParams.Error);
        if (MODE == SIX_STRING_MODE) dbgPrintf("Six strings mode\r\n");
        else if (MODE == ONE_STRING_MODE) dbgPrintf("One string mode\r\n");

        for (uint8_t i = 0; i < 6; i++) dbgPrintf("%d     %0.3f\r\n", i + 1, stringParams.result[i]);

        if (stringParams.Error == false){
			servoControl(&stringParams);
		}

        chThdSleepMilliseconds(10000);
    }
}
