#include "terminal_write.h"
#include "power_fft.h"
#include "adc_lld.h"

static uint16_t signal[MAIN_SIGNAL_LENGTH] = {0};
static float spec[SPEC_LENGTH] = {0};

void labview_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    adcSimpleRead(signal, MAIN_SIGNAL_LENGTH);
    fft(spec, signal);
    while (true) {
        for (uint16_t i = 0; i < SPEC_LENGTH; i++){
            dbgPrintf("%0.5f\r\n", spec[i]);
        }
        chThdSleepMilliseconds(1000000);
    }
}
