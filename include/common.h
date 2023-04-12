// Header file to select program to run

#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_

#include "hal.h"
#include "ch.h"
#include "chprintf.h"
#include "settings.h"
#include "stdlib.h"
#include "math.h"

// List of all possible programs
#define MAIN_ROUTINE                        0
#define ADC_TEST                            1
#define FFT_TEST                            2
#define FIND_PEAKS_TEST                     3
#define FIND_STRING_FREQS_TEST              4
#define LABVIEW_TEST                        5
#define ONE_STRING_MODE_TEST                6
#define SERVO_SIMPLE_TEST                   7
#define SIGNAL_RECORDING_TEST               8
#define SIX_STRING_MODE_TEST                9
#define INDICATION_TEST						10



// Selection of program to run
#define PROGRAM_ROUTINE SIX_STRING_MODE_TEST

#endif /* INCLUDE_COMMON_H_ */
