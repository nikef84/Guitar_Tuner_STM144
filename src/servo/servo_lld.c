#include "servo_lld.h"

/*
 * @brief   Setting the pwm configuration to control servos.
 *
 * @note    Controls four servos. From 1 to 4.
 *
 * @note    PWM_CONFIG_FREQUENCY / PWM_CONFIG_PERIOD = 50 Hz.
 *
 * @note    PWMD3 is used (TIM3).
 */
static PWMConfig pwm3cfg = {
    .frequency = PWM_CONFIG_FREQUENCY,
    .period    = PWM_CONFIG_PERIOD,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

/*
 * @brief   Setting the pwm configuration to control servos.
 *
 * @note    Controls two servos. From 5 to 6.
 *
 * @note    PWM_CONFIG_FREQUENCY / PWM_CONFIG_PERIOD = 50 Hz.
 *
 * @note    PWMD4 is used (TIM4).
 */
static PWMConfig pwm4cfg = {
    .frequency = PWM_CONFIG_FREQUENCY,
    .period    = PWM_CONFIG_PERIOD,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

/*
* @brief    Inits pwms and sets legs to the operating mode.
*
* @note     PWMD3 is used (TIM3).
*           PWMD4 is used (TIM4).
*
*/
void servoSimpleInit(void){
    palSetLineMode(PWM3_LINE_CH1,  PWM3_MODE_CH1); // PB4  - SERVO_1
    palSetLineMode(PWM3_LINE_CH2,  PWM3_MODE_CH2); // PB5  - SERVO_2
    palSetLineMode(PWM3_LINE_CH3,  PWM3_MODE_CH3); // PB0  - SERVO_3
    palSetLineMode(PWM3_LINE_CH4,  PWM3_MODE_CH4); // PB1  - SERVO_4
    palSetLineMode(PWM4_LINE_CH1,  PWM4_MODE_CH1); // PD12 - SERVO_5
    palSetLineMode(PWM4_LINE_CH2,  PWM4_MODE_CH2); // PD13 - SERVO_6

    pwmStart(PWMD3, &pwm3cfg);
    pwmStart(PWMD4, &pwm4cfg);
}

/*
 * @brief   Sets the voltage to the servo.
 *
 * @note    Possible voltages:
 *              Clockwise rotation          - (min = 710; max = 510);
 *              Counterclockwise rotation   - (min = 770; max = 790);
 *          These values may differ for defferent servos.
 *
* @note     PWMD3 is used (TIM3).
*           PWMD4 is used (TIM4).
*
* @param[in]    numOfServo  The number of the servo to which we want
*                           to set the voltage.
*               voltage
 */
void servoSetVoltage(uint8_t numOfServo, int16_t voltage){
    if (numOfServo <= PWM_MAX_CHANNEL && numOfServo > 0) {
        pwmEnableChannel(PWMD3, numOfServo - 1, voltage);
    }
    else if (numOfServo <= NUM_OF_SERVOS){
        pwmEnableChannel(PWMD4, numOfServo - (NUM_OF_SERVOS - 1), voltage);
    }
}

void servoStop(uint8_t numOfServo){
    if (numOfServo <= PWM_MAX_CHANNEL && numOfServo > 0) {
        pwmDisableChannel(PWMD3, numOfServo - 1);
    }
    else if (numOfServo <= NUM_OF_SERVOS){
        pwmDisableChannel(PWMD4, numOfServo - (NUM_OF_SERVOS - 1));
    }
}

void servoAllStop(void){
    for (uint8_t i = 1; i <= NUM_OF_SERVOS; i++) servoStop(i);
}

void servoSimpleUninit(void){
    servoAllStop();
    pwmStop(PWMD3);
    pwmStop(PWMD4);

    palSetLineMode(PWM3_LINE_CH1,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM3_LINE_CH2,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM3_LINE_CH3,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM3_LINE_CH4,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM4_LINE_CH1,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM4_LINE_CH2,  PAL_MODE_UNCONNECTED);
}
