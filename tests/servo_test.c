#include "ch.h"
#include "hal.h"
#include "common.h"
#include "terminal_write.h"


static PWMDriver *pwm3Driver = &PWMD3;
bool flag = false;

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

void palcb_button(void* args){
    args = args;
    flag = true;
}

#define SPEED1          900
#define SPEED2          950

/*
 * E9 - step
 * F13 - dir
 */
void servo_test(void)
{
    chSysInit();
    halInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");

    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    // Разрешаем прерывание, указываем callbcak функцию и передаем указатель на аргумент
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, palcb_button, NULL);

    uint16_t speed = SPEED1;
    palSetLineMode( PAL_LINE( GPIOB, 4 ),  PAL_MODE_ALTERNATE(2) );
    pwmStart( pwm3Driver, &pwm3conf );
    pwmEnableChannel( pwm3Driver, 0,speed);
    dbgPrintf("speed = %d\r\n", speed);

    while (true){
        if (flag == true){
            if (speed == SPEED1) speed = SPEED2;
            else speed = SPEED1;
            flag = false;
            pwmEnableChannel (pwm3Driver, 0,speed);
            palToggleLine(LINE_LED3);
            dbgPrintf("speed = %d\r\n", speed);

        }
        chThdSleepMilliseconds(100);
    }
}
