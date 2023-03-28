#include "find_string_freqs.h"

// An array that stores the values of the main signal.
static uint16_t mainSignalBuf[MAIN_SIGNAL_LENGTH] = {0};
// An array that stores the spectrum values of the main signal.
static float specBuf[SPEC_LENGTH] = {0};

// A structure that stores all data of peaks.
static peaksAllParams peaksParams = {
    .indicesOfFreqs = {0}, // Peak freq indices in the main signal array.
    .freqs = {0}, // Peak freqs.
    .ampOfFreqs = {0}, // The amplitudes of the found peaks.
    .lengthOfArrays = 0 // The number of found peaks.
};

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
void findStringParams(stringFreqsParams *stringParams){
    recordMainSignal(mainSignalBuf); // Records the signal from the sensor.
    fft(specBuf, mainSignalBuf); // Finds the spectrum of the signal.
    stringParams->Error = searchForRequiredPeaks(specBuf, &peaksParams); // Finds all possible peaks.
    // Finds real string freqs.
    if (stringParams->Error == false){
        if (MODE == SIX_STRING_MODE) sixStringMode(&peaksParams, stringParams);
        else if (MODE == ONE_STRING_MODE) oneStringMode(&peaksParams, stringParams);
    }
    else{
        stringParams->oneStringFreq = 0;
        writes_zeros_to_six_string_array(stringParams);
    }
}
