#ifndef INCLUDE_SERVO_SERVO_CONTROL_H_
#define INCLUDE_SERVO_SERVO_CONTROL_H_

#include "common.h"
#include "servo_lld.h"
#include "terminal_write.h"

#define SET_FREQ_HIGHER				0
#define SET_FREQ_LOWER				1

#define SIZE_OF_MB_BUF				1

void servoControl(stringFreqsParams *stringParams);

#endif /* INCLUDE_SERVO_SERVO_CONTROL_H_ */
