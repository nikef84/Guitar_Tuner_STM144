#include "../include/micro/adc_lld.h"
#include "terminal_write.h"
#include "power_fft.h"

static uint16_t signal[MAIN_SIGNAL_LENGTH] = {0};
static float spec[MAIN_SIGNAL_LENGTH / 2] = {0};


void fft_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    while (true) {
        adcSimpleRead(signal, MAIN_SIGNAL_LENGTH);
        dbgPrintf("signal = %d\r\n", signal[MAIN_SIGNAL_LENGTH-1]);
        fft(spec, signal);
        dbgPrintf("spec = %0.5f\r\n", spec[(MAIN_SIGNAL_LENGTH / 2) - 1]);
    }
}
