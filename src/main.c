#include "common.h"
#include "tests.h"

static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == ADC_TEST)
    adc_test();
#elif(PROGRAM_ROUTINE == FFT_TEST)
    fft_test();
#elif(PROGRAM_ROUTINE == FIND_PEAKS_TEST)
    find_peaks_test();
#elif(PROGRAM_ROUTINE == FIND_STRING_FREQS_TEST)
    find_string_freqs_test();
#elif(PROGRAM_ROUTINE == LABVIEW_TEST)
    labview_test();
#elif(PROGRAM_ROUTINE == ONE_STRING_MODE_TEST)
    one_string_mode_test();
#elif(PROGRAM_ROUTINE == SIGNAL_RECORDING_TEST)
    signal_recording_test();
#elif(PROGRAM_ROUTINE == SIX_STRING_MODE_TEST)
    six_string_mode_test();

#endif
}



int main(void) {
#if(PROGRAM_ROUTINE != MAIN_ROUTINE)
    testRoutines();

#else
    chSysInit();
    halInit();

    while(1);

#endif
}
