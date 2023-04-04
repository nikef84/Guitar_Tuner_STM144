#ifndef INCLUDE_SERVO_SERVO_LLD_H_
#define INCLUDE_SERVO_SERVO_LLD_H_

#include "common.h"

#define PWMD3                       &PWMD3
#define PWMD4                       &PWMD4

#define PWM_CONFIG_FREQUENCY        500000
#define PWM_CONFIG_PERIOD           10000

#define PWM3_LINE_CH1               PAL_LINE(GPIOB, 4)
#define PWM3_LINE_CH2               PAL_LINE(GPIOB, 5)
#define PWM3_LINE_CH3               PAL_LINE(GPIOB, 0)
#define PWM3_LINE_CH4               PAL_LINE(GPIOB, 1)
#define PWM4_LINE_CH1               PAL_LINE(GPIOD, 12)
#define PWM4_LINE_CH2               PAL_LINE(GPIOD, 13)

#define PWM3_MODE_CH1               PAL_MODE_ALTERNATE(2)
#define PWM3_MODE_CH2               PAL_MODE_ALTERNATE(2)
#define PWM3_MODE_CH3               PAL_MODE_ALTERNATE(2)
#define PWM3_MODE_CH4               PAL_MODE_ALTERNATE(2)
#define PWM4_MODE_CH1               PAL_MODE_ALTERNATE(2)
#define PWM4_MODE_CH2               PAL_MODE_ALTERNATE(2)

#define PWM_MAX_CHANNEL             4
#define NUM_OF_SERVOS               6

#define SERVO_1                     1
#define SERVO_2                     2
#define SERVO_3                     3
#define SERVO_4                     4
#define SERVO_5                     5
#define SERVO_6                     6




void servoSimpleInit(void);
void servoSetVoltage(uint8_t numOfServo, int16_t voltage);
void servoStop(uint8_t numOfServo);
void servoAllStop(void);
void servoSimpleUninit(void);


#endif /* INCLUDE_SERVO_SERVO_LLD_H_ */
