#include "terminal_write.h"
#include "fft.h"

static uint16_t signal[SIGNAL_LENGTH] = {0};
static float spec[SIGNAL_LENGTH/2] = {0};


void fftTest(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    while (true) {
        adcSimpleRead(signal, SIGNAL_LENGTH);
        dbgPrintf("signal = %d\r\n", signal[SIGNAL_LENGTH-1]);
        fft(spec, signal);
        dbgPrintf("spec = %0.5f\r\n", spec[(SIGNAL_LENGTH / 2) - 1]);
    }
}
