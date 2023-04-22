#include "servo_lld.h"

/*
 * @brief   Setting the pwm configuration to control servos.
 *
 * @note    Controls four servos. From 1 to 4.
 *
 * @note    PWM_CONFIG_FREQUENCY / PWM_CONFIG_PERIOD = 50 Hz.
 *
 * @note    PWMD1 is used (TIM1).
 */
static PWMConfig pwm1cfg = {
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
 * @brief   Inits pwms and sets legs to the operating mode.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 */
void servoSimpleInit(void){
    palSetLineMode(PWM1_LINE_CH1,  PWM1_MODE_CH1); // PE9  - SERVO_1
    palSetLineMode(PWM1_LINE_CH2,  PWM1_MODE_CH2); // PE11 - SERVO_2
    palSetLineMode(PWM1_LINE_CH3,  PWM1_MODE_CH3); // PE13 - SERVO_3
    palSetLineMode(PWM1_LINE_CH4,  PWM1_MODE_CH4); // PE14 - SERVO_4
    palSetLineMode(PWM4_LINE_CH1,  PWM4_MODE_CH1); // PD12 - SERVO_5
    palSetLineMode(PWM4_LINE_CH2,  PWM4_MODE_CH2); // PD13 - SERVO_6

    pwmStart(PWMD1, &pwm1cfg);
    pwmStart(PWMD4, &pwm4cfg);
}

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
void servoSetVoltage(uint8_t numOfServo, int16_t voltage){
    // Control of the first four servos.
    if (numOfServo <= PWM_MAX_CHANNEL && numOfServo > 0) {
        pwmEnableChannel(PWMD1, numOfServo - 1, voltage);
    }
    // Control of the last two servos.
    else if (numOfServo <= NUM_OF_STRINGS){
        pwmEnableChannel(PWMD4, numOfServo - (NUM_OF_STRINGS - 1), voltage);
    }
}

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
void servoStop(uint8_t numOfServo){
    // Control of the first four servos.
    if (numOfServo <= PWM_MAX_CHANNEL && numOfServo > 0) {
        pwmDisableChannel(PWMD1, numOfServo - 1);
    }
    // Control of the last two servos.
    else if (numOfServo <= NUM_OF_STRINGS){
        pwmDisableChannel(PWMD4, numOfServo - (NUM_OF_STRINGS - 1));
    }
}

/*
 * @brief   Stops all servos.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 */
void servoAllStop(void){
    for (uint8_t i = 1; i <= NUM_OF_STRINGS; i++) servoStop(i);
}

/*
 * @brief   Stops all servos and PWMs.
 *
 * @note   	Setting a safe state for used leg.
 *
 * @note    PWMD1 is used (TIM1).
 *          PWMD4 is used (TIM4).
 *
 */
void servoSimpleUninit(void){
    servoAllStop();
    pwmStop(PWMD1);
    pwmStop(PWMD4);

    palSetLineMode(PWM1_LINE_CH1,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM1_LINE_CH2,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM1_LINE_CH3,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM1_LINE_CH4,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM4_LINE_CH1,  PAL_MODE_UNCONNECTED);
    palSetLineMode(PWM4_LINE_CH2,  PAL_MODE_UNCONNECTED);
}
