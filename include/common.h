// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include <hal.h>
#include <ch.h>
#include <tests.h>
#include <chprintf.h>

// List of all possible programs
#define MAIN_ROUTINE                 0
#define BLINK_TEST                   1
#define STEPPER_MOTOR_TEST           2
#define TERMINAL_WRITE_TEST          3
#define ADC_TEST                     4
#define SIGNAL_RECORDING_TEST        5
#define FFT_TEST                     6



// Selection of program to run
#define PROGRAM_ROUTINE SIGNAL_RECORDING_TEST

#endif /* INCLUDE_COMMON_H_ */
