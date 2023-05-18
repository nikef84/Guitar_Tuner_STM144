#ifndef INCLUDE_SERVO_SERVO_CONTROL_H_
#define INCLUDE_SERVO_SERVO_CONTROL_H_

#include "common.h"
#include "servo_lld.h"
#include "indication.h"

// Direction of rotation of the servo.
#define SET_FREQ_HIGHER				1 // Counterclockwise.
#define SET_FREQ_LOWER				0 // Clockwise.

// The size of mailbox buffers.
#define SIZE_OF_MB_BUF				1

// The max and min time interval during which we will control the servo.
#define ROTATE_TIME_LIM_MAX 		3000 // ms
#define ROTATE_TIME_LIM_MIN 		30  // ms


/*
 * @brief	Inits servo threads, mailboxes, pwms and sets legs.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 * @param[out]		All threads, mailboxes and pwms have been started.
 */
msg_t servoInit(void);

/*
 * @brief	Distributes tasks to each sevro.
 *
 * @note	A msg contains a current freq of the string.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 */
void servoControl(stringFreqsParams *stringParams);

/*
 * @brief	Stops servo threads and pwms.
 *
 * @param[out]    msg   A message is about if thread is stopped or not.
 *
 * @note   Not verified.
 */
msg_t servoUninit(void);


#endif /* INCLUDE_SERVO_SERVO_CONTROL_H_ */
