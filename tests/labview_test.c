#include "terminal_write.h"
#include "power_fft.h"
#include "signal_recording.h"

static uint16_t signal[MAIN_SIGNAL_LENGTH] = {0};
static float spec[SPEC_LENGTH] = {0};

void labview_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    adcSimpleInit();
    recordMainSignal(signal);
    uint16_t period = SPEC_LENGTH / 4;
    fft(spec, signal);
    for (uint8_t j = 0; j < 4; j++){
        for (uint16_t i = j*period; i < (j + 1) * period; i++){
            dbgPrintf("%0.3f\r\n", spec[i]);
        }
        chThdSleepMilliseconds(15000);
    }
    while (true) {
//        for (uint8_t j = 0; j < 8; j++){
//            for (uint16_t i = j*period; i < (j + 1) * period; i++){
//                dbgPrintf("%d\r\n", signal[i]);
//            }
//            chThdSleepMilliseconds(15000);
//        }
        chThdSleepMilliseconds(1000000);
    }
}
