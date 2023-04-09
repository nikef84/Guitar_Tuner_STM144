#include "tests.h"
#include "servo_lld.h"
#include "terminal_write.h"

bool flag = false;

void palcb_button(void* args){
    args = args;
    flag = true;
}

#define SPEED1          900
#define SPEED2          0


void servo_simple_test(void)
{
    chSysInit();
    halInit();
    servoSimpleInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");

    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
    palSetPadCallback(GPIOC, GPIOC_BUTTON, palcb_button, NULL);

    uint16_t speed = SPEED1;
    dbgPrintf("speed = %d\r\n", speed);
    servoSetVoltage(5, speed);
    servoSetVoltage(6, speed);
    while (true){
        if (flag == true){
            if (speed == SPEED1) {
                speed = SPEED2;
                servoStop(5);
                servoStop(6);
            }
            else {
                speed = SPEED1;
                servoSetVoltage(5, speed);
                servoSetVoltage(6, speed);
            }
            flag = false;
            palToggleLine(LINE_LED3);
            dbgPrintf("speed = %d\r\n", speed);

        }
        chThdSleepMilliseconds(100);
    }
}
