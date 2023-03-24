#include "ch.h"
#include "hal.h"
#include "common.h"


static PWMDriver *pwm3Driver = &PWMD3;

PWMConfig pwm3conf = {
    .frequency = 500000,
    .period    = 10000,
    .callback  = NULL,
    .channels  = {
                  {.mode = PWM_OUTPUT_ACTIVE_HIGH, .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL},
                  {.mode = PWM_OUTPUT_DISABLED,    .callback = NULL}
                  },
    .cr2        = 0,
    .dier       = 0
};

/*
 * E9 - step
 * F13 - dir
 */
void servo_test(void)
{
    chSysInit();
    halInit();
    palSetLineMode( PAL_LINE( GPIOB, 4 ),  PAL_MODE_ALTERNATE(2) );
    pwmStart( pwm3Driver, &pwm3conf );
    pwmEnableChannel( pwm3Driver, 0,400);

    while (true);
}
