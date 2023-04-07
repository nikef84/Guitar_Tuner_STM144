#ifndef INCLUDE_MODES_SIX_STRING_MODE_H_
#define INCLUDE_MODES_SIX_STRING_MODE_H_

#include "common.h"
#include "terminal_write.h"

// Dimensions of "freqsDecomposition".
#define NUM_OF_FREQS_IN_SEPARATION          10 // Number of possible freqs for each string.

// Margins to check if some value is in some range.
#define MULT_CHECK_SIX_STR_MARGIN           5 // Hz
#define FIND_ALL_FREQS_MARGIN               0.05 // Abs

#define MAX_MULTIPLIER_FOR_LOST_FREQS       5


// The limits in which freqs of each string can be.
typedef struct{
    float upperLimit;
    float lowerLimit;
} sixStringLimitsParams;


/*
 * @brief   Writes zeros to "stringParams.sixStringFreqs".
 *
 * @note    Always used when some error has occurred.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 */
void writes_zeros_to_six_string_array(stringFreqsParams *stringParams);


/*
 * @brief   Checks if the received data is correct and finds real freqs of six strings.
 *
 * @note    If the "stringParams->sixStringFreq" is {0}, then we had an error.
 *
 * @note    May not find all string frequencies.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 */
void sixStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams);

#endif /* INCLUDE_MODES_SIX_STRING_MODE_H_ */
