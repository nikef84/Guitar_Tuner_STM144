#ifndef INCLUDE_SERVO_SERVO_LLD_H_
#define INCLUDE_SERVO_SERVO_LLD_H_

#include "common.h"

// Which timers the PWM uses.
#define PWMD1                       &PWMD1 // TIM1
#define PWMD4                       &PWMD4 // TIM4

// PWMs configuration. PWMd3 and PWMD4 have the same conf.
#define PWM_CONFIG_FREQUENCY        500000
#define PWM_CONFIG_PERIOD           10000

// Legs and modes which are used to control servos.
#define PWM1_LINE_CH1               PAL_LINE(GPIOE, 9)  // SERVO_1
#define PWM1_LINE_CH2               PAL_LINE(GPIOE, 11) // SERVO_2
#define PWM1_LINE_CH3               PAL_LINE(GPIOE, 13) // SERVO_3
#define PWM1_LINE_CH4               PAL_LINE(GPIOE, 14) // SERVO_4
#define PWM4_LINE_CH1               PAL_LINE(GPIOD, 12) // SERVO_5
#define PWM4_LINE_CH2               PAL_LINE(GPIOD, 13) // SERVO_6

#define PWM1_MODE_CH1               PAL_MODE_ALTERNATE(1) // SERVO_1
#define PWM1_MODE_CH2               PAL_MODE_ALTERNATE(1) // SERVO_2
#define PWM1_MODE_CH3               PAL_MODE_ALTERNATE(1) // SERVO_3
#define PWM1_MODE_CH4               PAL_MODE_ALTERNATE(1) // SERVO_4
#define PWM4_MODE_CH1               PAL_MODE_ALTERNATE(2) // SERVO_5
#define PWM4_MODE_CH2               PAL_MODE_ALTERNATE(2) // SERVO_6

// They are necessary for splitting all servos into two timers.
// Do NOT touch these values!!!
#define PWM_MAX_CHANNEL             4 // Max num of channels in one timer.



/*
 * @brief   Inits pwms and sets legs to the operating mode.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 */
void servoSimpleInit(void);

/*
 * @brief   Sets the voltage to the servo.
 *
 * @note    Possible voltages:
 *              Clockwise rotation          - (min = 710; max = 510);
 *              Counterclockwise rotation   - (min = 770; max = 790).
 *          These values may differ for defferent servos.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 * @param[in]    numOfServo  The number of the servo to which we want
 *                           to set the voltage.
 *
 *               voltage     A coefficient that sets the length of
 *                           a high signal relative to the signal period.
 *                           Max value - 10000.
 *
 */
void servoSetVoltage(uint8_t numOfServo, int16_t voltage);

/*
 * @brief   Stops the servo.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 * @param[in]   numOfServo  The number of the servo to which we want
 *                          to set the voltage.
 *
 */
void servoStop(uint8_t numOfServo);

/*
 * @brief   Stops all servos.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 */
void servoAllStop(void);

/*
 * @brief   Stops all servos and PWMs.
 *
 * @note   Setting a safe state for used leg.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 */
void servoSimpleUninit(void);


#endif /* INCLUDE_SERVO_SERVO_LLD_H_ */
