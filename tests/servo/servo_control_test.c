#include "servo_control.h"
#include "terminal_write.h"
#include "tests.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .result = {311, 0, 0, 0, 0, 0}
};


void servo_control_test(void) {


    halInit();
    chSysInit();
    debugStreamInit();
	dbgPrintf("Start\r\n");
	servoInit();
	chThdSleepMilliseconds(5000);

    if (stringParams.Error == false){
    	servoControl(&stringParams);
    }

    while (true) {
    	palToggleLine(LINE_LED3);
        chThdSleepMilliseconds(1000);
    }
}
