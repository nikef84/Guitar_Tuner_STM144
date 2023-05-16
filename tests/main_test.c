#include "tests.h"
#include "signal_recording.h"
#include "indication.h"
#include "find_string_freqs.h"
#include "servo_control.h"
#include "terminal_write.h"


static stringFreqsParams stringParams = {
	.result = {0},
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0}
};

// An array that stores the values of the main signal.
static uint16_t mainSignalBuf[MAIN_SIGNAL_LENGTH] = {0};

void main_test(void) {
    halInit();
    chSysInit();

    debugStreamInit();
    adcSimpleInit();
    indicationInit();
    servoInit();

    chThdSleepMilliseconds(1000);

    dbgPrintf("Start\r\n");

    while (true) {
    	setPotentPermission(true);
    	dbgPrintf("ok\r\n");
    	recordMainSignal(mainSignalBuf);
    	dbgPrintf("okeeeeee\r\n");
    	setPotentPermission(false);
    	chThdSleepMilliseconds(500);

        findStringParams(mainSignalBuf, &stringParams);

        dbgPrintf("Error = %d\r\n", stringParams.Error);
        if (getOperatingMode() == SIX_STRING_MODE) dbgPrintf("Six strings mode\r\n");
        else if (getOperatingMode() == ONE_STRING_MODE) dbgPrintf("One string mode\r\n");
        for (uint8_t i = 0; i < 6; i++) dbgPrintf("%d     %0.3f\r\n", i + 1, stringParams.result[i]);

        servoControl(&stringParams);
        chThdSleepMilliseconds(4000);

        if (checkNeedToResetLeds() == true){
			chThdSleepMilliseconds(5000);
			resetsLeds();
		}
    }
}
