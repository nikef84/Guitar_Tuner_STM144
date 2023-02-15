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
