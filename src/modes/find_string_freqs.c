#include "find_string_freqs.h"

// An array that stores the spectrum values of the main signal.
static float specBuf[SPEC_LENGTH] = {0};

// A structure that stores all data of peaks.
static peaksAllParams peaksParams = {
    .freqs = {0}, // Peak freqs.
    .ampOfFreqs = {0}, // The amplitudes of the found peaks.
    .lengthOfArrays = 0 // The number of found peaks.
};

/*
 * @brief   Finds siganl spectrum and uses it to find the real freqs of the strings.
 *
 * @note    ADC1 is used. GPTD5 is used.
 *
 * @note    May not find all string frequencies.
 *
 * @note    If the "stringParams->sixStringFreq" is {0} or
 *                  stringParams->oneStringFreq" is  0, then we had an error.
 *
 * @param[in]   mainSignalBuf       An array in which data will be write from the adc.
 * 				stringParams    	The pointer to the structure in which all data of strings are stored.
 */
void findStringParams(uint16_t *mainSignalBuf, stringFreqsParams *stringParams){
    fft(specBuf, mainSignalBuf); // Finds the spectrum of the signal.
    stringParams->Error = searchForRequiredPeaks(specBuf, &peaksParams); // Finds all possible peaks.
    for (uint8_t i = 0; i < peaksParams.lengthOfArrays; i++){
    	dbgPrintf("%0.3f\r\n", peaksParams.freqs[i]);
    }
    // Finds real string freqs.
    if (stringParams->Error == false){
        if (getOperatingMode() == SIX_STRING_MODE) sixStringMode(&peaksParams, stringParams);
        else if (getOperatingMode() == ONE_STRING_MODE) oneStringMode(&peaksParams, stringParams);
    }
    else{
        stringParams->oneStringFreq = 0;
        writes_zeros_to_six_string_array(stringParams);
    }
}
