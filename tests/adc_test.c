#include "adc_lld.h"
#include "terminal_write.h"

#define ARRAY_LENGTH        5
static uint16_t array[ARRAY_LENGTH] = {0};

void adcTest(void) {
    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    systime_t begin = chVTGetSystemTime();
    uint16_t max, min;
    while (true) {
        adcSimpleRead(array, ARRAY_LENGTH);
        max = array[0];
        min = array[0];
        for (uint16_t i = 0; i < ARRAY_LENGTH; i++){
            if (array[i] > max) max = array[i];
            else if (array[i] < min) min = array[i];
        }
        systime_t end = chVTGetSystemTime();
        dbgPrintf("time = %d\r\n", end - begin);
        dbgPrintf("max = %d\r\n", max);
        dbgPrintf("min = %d\r\n", min);
        begin = chVTGetSystemTime();
          chThdSleepMilliseconds(1000);
    }
}
