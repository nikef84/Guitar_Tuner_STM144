#include "ch.h"
#include "hal.h"
#include "common.h"


static PWMDriver *pwm1Driver = &PWMD1;

PWMConfig pwm1conf = {
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
void pwmTest(void)
{
    chSysInit();
    halInit();
    palSetLineMode( PAL_LINE( GPIOE, 9 ),  PAL_MODE_ALTERNATE(1) );
    palSetPadMode(GPIOF, 13, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOF, 13);
    pwmStart( pwm1Driver, &pwm1conf );
    pwmEnableChannel( &PWMD1, 0, 5000 );

    while (true);
}
