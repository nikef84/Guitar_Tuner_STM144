#include "tests.h"
#include "indication.h"
#include "terminal_write.h"

static uint8_t newVal[6] = {LED_NOT_ACTIVE};
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
		if (getOperatingMode() == ONE_STRING_MODE){
			uint8_t string = getCurrentString();
			for (uint8_t i = 0; i < 6; i++){
				newVal[i] = LED_NOT_ACTIVE;
			}
			newVal[string - 1] = LED_GREEN_LIGHT;
			num = 0;
		}
		else{
			for (uint8_t i = 0; i < 6; i++){
				newVal[i] = LED_RED_LIGHT;
			}
			newVal[num] = LED_GREEN_LIGHT;
			newVal[5-num] = LED_GREEN_LIGHT;

			num += 1;
		}
		setStringLeds(newVal);
		chThdSleepMilliseconds(500);
		if (checkNeedToResetLeds() == true){
			chThdSleepMilliseconds(5000);
			resetsLeds();
			num = 0;

		}
		setPotentPermission(true);
    }
}
