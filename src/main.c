#include "common.h"

static inline void testRoutines(void) {
#if(PROGRAM_ROUTINE == BLINK_TEST)
    blinkTest();
#elif(PROGRAM_ROUTINE == STEPPER_MOTOR_TEST)
    stepperMotorTest();
#elif(PROGRAM_ROUTINE == TERMINAL_WRITE_TEST)
    terminalWriteTest();
#elif(PROGRAM_ROUTINE == ADC_TEST)
    adcTest();
#elif(PROGRAM_ROUTINE == SIGNAL_RECORDING_TEST)
    signalRecordingTest();
#elif(PROGRAM_ROUTINE == FFT_TEST)
    fftTest();
#elif(PROGRAM_ROUTINE == FIND_PEAKS_TEST)
    findPeaksTest();
#elif(PROGRAM_ROUTINE == SORT_FUNCS_TEST)
    sortFuncsTest();
#elif(PROGRAM_ROUTINE == PWM_TEST)
    pwmTest();
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
