#include "tests.h"
#include "indication.h"
#include "terminal_write.h"


void indication_test(void)
{
    chSysInit();
    halInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");

    indicationInit();
    uint8_t num = 0;
	while (true){
		chThdSleepMilliseconds(5000);
		setPotentPermission(false);
		dbgPrintf("Leds on\r\n");
		if (getOperatingMode() == ONE_STRING_MODE){
			dbgPrintf("1\r\n");
			uint8_t string = getCurrentString();
			for (uint8_t i = 1; i <= NUM_OF_STRINGS; i++){
				if (i != string) setStringLeds(LED_RED_LIGHT, i);
			}
			chThdSleepMilliseconds(1000);
			setStringLeds(LED_GREEN_LIGHT, string);
			num = 0;
		}
		else{
			for (uint8_t i = 4; i <= 6; i++){
				setStringLeds(LED_RED_LIGHT, i);
			}
			dbgPrintf("ok\r\n");

			setStringLeds(LED_GREEN_LIGHT, 6 - num);
			chThdSleepMilliseconds(1000);

			for (uint8_t i = 1; i <= 3; i++){
				setStringLeds(LED_RED_LIGHT, i);
			}
			setStringLeds(LED_GREEN_LIGHT, num + 1);


			num += 1;
		}

		chThdSleepMilliseconds(500);
		if (checkNeedToResetLeds() == true){
			chThdSleepMilliseconds(5000);
			resetsLeds();
			num = 0;

		}
		setPotentPermission(true);
	}





//    uint8_t num = 0;
//    while (true){
//    	chThdSleepMilliseconds(5000);
//    	setPotentPermission(false);
//		if (getOperatingMode() == ONE_STRING_MODE){
//			uint8_t string = getCurrentString();
//			for (uint8_t i = 0; i < 6; i++){
//				newVal[i] = LED_NOT_ACTIVE;
//			}
//			newVal[string - 1] = LED_GREEN_LIGHT;
//			num = 0;
//		}
//		else{
//			for (uint8_t i = 0; i < 6; i++){
//				newVal[i] = LED_RED_LIGHT;
//			}
//			newVal[num] = LED_GREEN_LIGHT;
//			newVal[5-num] = LED_GREEN_LIGHT;
//
//			num += 1;
//		}
//		setStringLeds(newVal);
//		chThdSleepMilliseconds(500);
//		if (checkNeedToResetLeds() == true){
//			chThdSleepMilliseconds(5000);
//			resetsLeds();
//			num = 0;
//
//		}
//		setPotentPermission(true);
//    }
}
