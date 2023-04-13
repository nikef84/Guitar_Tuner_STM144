#ifndef INCLUDE_FINDPEAKS_FIND_PEAKS_H_
#define INCLUDE_FINDPEAKS_FIND_PEAKS_H_

#include "common.h"
#include "indication.h"

// The beginning and the end of the spectrum. In Hz.
#define SPEC_FREQ_MAX                   (GPT_CONFIG_FREQUENCY / GPT_PERIOD) / 2
#define SPEC_FREQ_MIN                   0

// It is added to investigated frequency to find if they are located nearby. In Hz.
// Depends on operating mode.
#define NEAREST_FREQS_RANGE_SIX_STR     6  // Hz.
#define NEAREST_FREQS_RANGE_ONE_STR     30 // Hz.

// In the range from 0 to "this limit", there is a lot of incorrect data.
#define TRASH_DATA_LIMIT                50 // Hz.

/*
 * @brief   Splits the spectrum into groups, which has its own limit.
 *
 * @note    minFreq     The start frequency of group. In Hz.
 *          maxFreq     The last frequency of group. In Hz.
 *          limit       The minimum value of the limit for finding a peak in a given group.
 */
typedef struct
{
    uint16_t minFreq;
    uint16_t maxFreq;
    float limit;
} findPeaksSeparat;

/*
 * @brief   The maximum value of the amplitude in the spectrum.
 *
 * @note    index       The position in the spectrum at which the amplitude is highest.
 *          amplitude   The value of highest peak in the spectrum.
 */
typedef struct
{
    uint16_t index;
    float amplitude;
} findMaxFreq;


/*
 * @brief   Finds all required peaks in the spectrum.
 *
 * @note    Maximum lenght of peaks is defined in PEAKS_MAX_LENGTH (settings.h).
 *
 * @param[in]   spectrum        The pointer to the spectrum.
 *              peaksParams     The pointer to the structure in which all data of peaks are stored.
 *
 * @param[out]  true  - We found more peaks than it should be. (PEAKS_MAX_LENGTH)
 *              false - Everything is OK. We found less peaks than it should be.
 */
bool searchForRequiredPeaks(float *spectrum, peaksAllParams *peaksParams);

#endif /* INCLUDE_FINDPEAKS_FIND_PEAKS_H_ */
