#include "servo_control.h"


static float trueFreqs[NUM_OF_STRINGS] = {82.4, 110, 146.83, 196, 246.94, 329.63};

static float servosCoefTime[NUM_OF_STRINGS] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};

static uint16_t servosSpeed	[2][NUM_OF_STRINGS] = {{870, 870, 870, 870, 870, 870},
												   {610, 610, 610, 610, 610, 610}};


static mailbox_t mb_servo_1;
static msg_t mb_servo_1_buffer[SIZE_OF_MB_BUF];

static thread_t *tp_servo_1;
static THD_WORKING_AREA(wa_servo_1, 256);

static THD_FUNCTION(servo_1, arg){
	chRegSetThreadName("Servo 1");

	(void)arg;
	float stringFreq;
	uint16_t time;
	msg_t msgError, msgResult;

	while (!chThdShouldTerminateX()){
		msgError = chMBFetchTimeout(&mb_servo_1, &msgResult, TIME_INFINITE);
		stringFreq = *((float*) &msgResult);

		if (msgError == MSG_OK && stringFreq != 0){

			time = roundf((servosCoefTime[STRING_1 - 1] * fabs(trueFreqs[STRING_1 - 1] - stringFreq)) *1000);

			if (trueFreqs[STRING_1 - 1] - stringFreq > 0){
				servoSetVoltage(STRING_1, servosSpeed[SET_FREQ_HIGHER][STRING_1 - 1]);
				dbgPrintf("Servo 1 turns to INcrease\r\n");
			}
			else {
				servoSetVoltage(STRING_1, servosSpeed[SET_FREQ_LOWER][STRING_1 - 1]);
				dbgPrintf("Servo 1 turns to DEcrease\r\n");
			}

			chThdSleepMilliseconds(time);
			servoStop(STRING_1);
		}
		else dbgPrintf("Servo 1 doesn't rotate\r\n");
	}
	chThdExit(MSG_OK);
}


void servo_init(void){
	chMBObjectInit(&mb_servo_1, mb_servo_1_buffer, SIZE_OF_MB_BUF);
	tp_servo_1 = chThdCreateStatic(wa_servo_1, sizeof(wa_servo_1), NORMALPRIO, servo_1, NULL);
}

void send_msgs(stringFreqsParams *stringParams){
	msg_t tmp = *((msg_t *) &stringParams->sixStringFreqs[1]);
	chMBPostTimeout(&mb_servo_1, tmp, TIME_IMMEDIATE);
}

void servoControl(stringFreqsParams *stringParams){
	servoSimpleInit();
	servo_init();
	send_msgs(stringParams);
}

