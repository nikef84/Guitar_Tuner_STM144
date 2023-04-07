#include "servo_control.h"
#include "tests.h"


static stringFreqsParams stringParams = {
    .oneStringFreq = 0,
    .Error = false,
    .sixStringFreqs = {0, 107.354, 0, 0, 0, 0}
};


void servo_control_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
	dbgPrintf("Start\r\n");
	chThdSleepMilliseconds(5000);


    while (true) {
        if (stringParams.Error == false){
        	servoControl(&stringParams);
        }
        chThdSleepMilliseconds(10000);
    }
}
