#include "common.h"
#include "tests.h"
#include "terminal_write.h"

#define BUFFER_SIZE 100

mailbox_t adc_mb;
msg_t adc_mb_buffer[BUFFER_SIZE];

void mailbox_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    chMBObjectInit(&adc_mb, adc_mb_buffer, BUFFER_SIZE);
    msg_t my_msg;
    msg_t num = 1;
    msg_t num1 = 2;
    msg_t msg = chMBPostTimeout(&adc_mb, num1, TIME_IMMEDIATE);
    msg = chMBPostTimeout(&adc_mb, num, TIME_IMMEDIATE);
    if (msg == MSG_OK){
    	msg = chMBFetchTimeout(&adc_mb, &my_msg, TIME_MS2I(500));
    	if (msg == MSG_OK){
    		dbgPrintf("%d\r\n", my_msg);
    	}
    	else dbgPrintf("not receive\r\n");
    	msg = chMBFetchTimeout(&adc_mb, &my_msg, TIME_MS2I(500));
		if (msg == MSG_OK){
			dbgPrintf("%d\r\n", my_msg);
		}
		else dbgPrintf("not receive\r\n");
    }
    else dbgPrintf("not send\r\n");
    while (true) {
        chThdSleepMilliseconds(10000);
    }
}
