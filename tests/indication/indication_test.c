#include "tests.h"
#include "indication.h"
#include "terminal_write.h"

static uint8_t newVal[6] = {DIODE_NOT_ACTIVE};
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
				newVal[i] = DIODE_NOT_ACTIVE;
			}
			newVal[string - 1] = DIODE_GREEN_LIGHT;
		}
		else{
			for (uint8_t i = 0; i < 6; i++){
				newVal[i] = DIODE_RED_LIGHT;
			}
			newVal[num] = DIODE_GREEN_LIGHT;
			newVal[5-num] = DIODE_GREEN_LIGHT;

			num += 1;
		}
		setDiodStrings(newVal);
		chThdSleepMilliseconds(500);
		if (checkNeedToResetDiodes() == true){
			chThdSleepMilliseconds(5000);
			resetsDiods();
			num = 0;

		}
		setPotentPermission(true);
    }
}
