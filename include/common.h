// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "hal.h"
#include "ch.h"
#include "tests.h"
#include "chprintf.h"
#include "settings.h"
#include "stdlib.h"
#include "math.h"

// List of all possible programs
#define MAIN_ROUTINE                        0
#define BLINK_TEST                          1
#define STEPPER_MOTOR_TEST                  2
#define TERMINAL_WRITE_TEST                 3
#define ADC_TEST                            4
#define SIGNAL_RECORDING_TEST               5
#define FFT_TEST                            6
#define FIND_PEAKS_TEST                     7
#define SORT_FUNCS_TEST                     8
#define PWM_TEST                            9
#define LABVIEW_TEST                        10
#define ONE_STRING_MODE_TEST                11
#define SIX_STRING_MODE_TEST                12
#define FIND_STRING_FREQS_TEST              13



// Selection of program to run
#define PROGRAM_ROUTINE LABVIEW_TEST

#endif /* INCLUDE_COMMON_H_ */
