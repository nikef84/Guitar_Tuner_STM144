#include "tests.h"
#include "servo_lld.h"
#include "terminal_write.h"

bool flag = false;

void palcb_button(void* args){
    args = args;
    flag = true;
}

// Clocwise(lower): min = 710, max = 510; Counterclockwise: min = 770, max = 1000.
#define SPEED1          510
#define SPEED2          0


//void servo_simple_test(void)
//{
//    chSysInit();
//    halInit();
//    servoSimpleInit();
//    debugStreamInit();
//    dbgPrintf("Start\r\n");
//
//    palSetPadMode(GPIOC, GPIOC_BUTTON, PAL_MODE_INPUT_PULLDOWN);
//    palEnablePadEvent(GPIOC, GPIOC_BUTTON, PAL_EVENT_MODE_RISING_EDGE);
//    palSetPadCallback(GPIOC, GPIOC_BUTTON, palcb_button, NULL);
//
//    uint16_t speed = SPEED1;
//    dbgPrintf("speed = %d\r\n", speed);
//    servoSetVoltage(5, speed);
//    servoSetVoltage(6, speed);
//    while (true){
//        if (flag == true){
//            if (speed == SPEED1) {
//                speed = SPEED2;
//                servoStop(2);
//                servoStop(1);
//            }
//            else {
//                speed = SPEED1;
//                servoSetVoltage(2, speed);
//                servoSetVoltage(1, speed);
//            }
//            flag = false;
//            palToggleLine(LINE_LED3);
//            dbgPrintf("speed = %d\r\n", speed);
//
//        }
//        chThdSleepMilliseconds(100);
//    }
//}

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
    servoSetVoltage(4, speed);
    while (true){

			chThdSleepMilliseconds(500);
			//servoStop(6);



        chThdSleepMilliseconds(10000);
    }
}
