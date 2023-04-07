#include "common.h"
#include "tests.h"
#include "terminal_write.h"

#define BUFFER_SIZE 100

mailbox_t adc_mb;
msg_t adc_mb_buffer[BUFFER_SIZE];
float num[] = {6.2, 5.3, 8.4};
msg_t my_msg;

void button(void* args){
    args = args;

    msg_t tmp = *((msg_t *) &num[0]);

    if (chMBPostTimeout(&adc_mb, tmp, TIME_IMMEDIATE) == MSG_OK){
    }
    else dbgPrintf("not send\r\n");
}

static thread_t *tp_servo;
static THD_WORKING_AREA(waServo, 256);

static THD_FUNCTION(servoThread, arg){
	(void)arg;
	chRegSetThreadName("Servo control");
	while (!chThdShouldTerminateX()){
		if (chMBFetchTimeout(&adc_mb, &my_msg, TIME_INFINITE) == MSG_OK){

			dbgPrintf("%f\r\n", *((float*) &my_msg));
		}
		else dbgPrintf("nor recieve\r\n");
	}
	chThdExit(MSG_OK);
}


void mailbox_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();

    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
	palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
	palSetPadCallback(GPIOC, GPIOC_BUTTON, button, NULL);
	dbgPrintf("start\r\n");
	tp_servo = chThdCreateStatic(waServo, sizeof(waServo), NORMALPRIO, servoThread, NULL);

    chMBObjectInit(&adc_mb, adc_mb_buffer, BUFFER_SIZE);
    while (true) {

        chThdSleepMilliseconds(10000);
    }
}
