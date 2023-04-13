#include "servo_control.h"
#include "find_string_freqs.h"
#include "terminal_write.h"
#include "signal_recording.h"
#include "tests.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0},
	.result = {0}
};

// An array that stores the values of the main signal.
static uint16_t mainSignalBuf[MAIN_SIGNAL_LENGTH] = {0};

void servo_with_micro_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
	dbgPrintf("Start\r\n");
	adcSimpleInit();
	setOperatingMode(SIX_STRING_MODE);
	setCurrentString(0);
	servoInit();
    while (true) {
    	recordMainSignal(mainSignalBuf);
        findStringParams(mainSignalBuf, &stringParams);
        dbgPrintf("Error = %d\r\n", stringParams.Error);
        if (getOperatingMode() == SIX_STRING_MODE) dbgPrintf("Six strings mode\r\n");
        else if (getOperatingMode() == ONE_STRING_MODE) dbgPrintf("One string mode\r\n");

        for (uint8_t i = 0; i < 6; i++) dbgPrintf("%d     %0.3f\r\n", i + 1, stringParams.result[i]);

        if (stringParams.Error == false){
			servoControl(&stringParams);
		}

        chThdSleepMilliseconds(10000);
    }
}
