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
#define FFT_TEST                            1
#define FIND_PEAKS_TEST                     2
#define ADC_TEST                            3
#define SIGNAL_RECORDING_TEST               4
#define FIND_STRING_FREQS_TEST              5
#define LABVIEW_TEST                        6
#define ONE_STRING_MODE_TEST                7
#define SIX_STRING_MODE_TEST                8
#define MAILBOX_TEST                		9
#define SERVO_CONTROL_TEST                	10
#define SERVO_SIMPLE_TEST                   11
#define SERVO_WITH_MICRO_TEST               12
#define INDICATION_TEST						13
#define MAIN_TEST							14



// Selection of program to run
#define PROGRAM_ROUTINE ONE_STRING_MODE_TEST


#endif /* INCLUDE_COMMON_H_ */
