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

    while (true){
        chThdSleepMilliseconds(1000);
    }
}
