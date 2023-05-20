#ifndef INCLUDE_MODES_ONE_STRING_MODE_H_
#define INCLUDE_MODES_ONE_STRING_MODE_H_

#include "common.h"
#include "six_string_mode.h"
#include "indication.h"

#define DIFF_FREQS_LENGTH               PEAKS_MAX_LENGTH - 1
// Margins to check if some value is in some range.
#define MULT_CHECK_ONE_STR_MARGIN       0.15 // Abs
#define FIND_REAL_FREQ_MARGIN           5 // Hz

/* @brief   Limit to check if we have a multiply noise.
 *
 * @Example     array = {100, 300, 600}
 *              diif  = {200, 300}
 *
 *              300 / 100 = 3 > 2.1 then 100 - a multiply noise.
 */
#define MULTIPLY_NOISE_CHECK_LIMIT      3.1 // Abs



/*
 * @brief   Checks if the received data is correct and finds a real freq of one string.
 *
 * @note    If the "stringParams->oneStringFreq" is "0", then we had an error.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 */
void oneStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams);

void oneStringModeForSixStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams);

#endif /* INCLUDE_MODES_ONE_STRING_MODE_H_ */
