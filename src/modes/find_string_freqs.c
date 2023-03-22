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
    uint16_t period = SPEC_LENGTH / 4;

    searchForRequiredPeaks(specBuf, &peaksParams); // Finds all possible peaks.
    for (uint8_t j = 0; j < 4; j++){
        for (uint16_t i = j*period; i < (j + 1) * period; i++){
           dbgPrintf("%0.3f\r\n", specBuf[i]);
        }
        chThdSleepMilliseconds(15000);
    }
    // Finds real string freqs.
    if (MODE == SIX_STRING_MODE) sixStringMode(&peaksParams, stringParams);
    else if (MODE == ONE_STRING_MODE) oneStringMode(&peaksParams, stringParams);
}
