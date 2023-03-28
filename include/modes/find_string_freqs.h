#ifndef INCLUDE_MODES_FIND_STRING_FREQS_H_
#define INCLUDE_MODES_FIND_STRING_FREQS_H_

#include "common.h"
#include "six_string_mode.h"
#include "one_string_mode.h"
#include "signal_recording.h"
#include "power_fft.h"
#include "find_peaks.h"

/*
 * @brief   Records the signal from the sensor, finds its spectrum and uses it
 *          to find the real freqs of the strings.
 *
 * @note    ADC1 is used. GPTD3 is used.
 *
 * @note    May not find all string frequencies.
 *
 * @note    If the "stringParams->sixStringFreq" is {0} or
 *                  stringParams->oneStringFreq" is  0, then we had an error.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 *
 */
void findStringParams(stringFreqsParams *stringParams);


#endif /* INCLUDE_MODES_FIND_STRING_FREQS_H_ */
