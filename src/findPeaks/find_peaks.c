#include "find_peaks.h"

// @brief   The size of the "separations" array.
#define SEPARATIONS_LENGTH              6
// @brief   The smallest "limit" value in the "separations".
static float separationsLimitMin;
// It is added to investigated frequency to find if they are located nearby. In Hz.
static uint8_t nearestFreqRange;

/*
 * @brief   Splits the spectrum into groups, which has its own limit.
 *
 * @note    For one string mode!
 *
 * @note    minFreq     The start frequency of group. In Hz.
 *          maxFreq     The last frequency of group. In Hz.
 *          limit       The minimum value of the limit for finding a peak in a given group.
 */
static findPeaksSeparat separatOneStr[] = {
    {.minFreq = SPEC_FREQ_MIN, .maxFreq = 95           , .limit = 50 },
    {.minFreq = 95           , .maxFreq = 215          , .limit = 60 },
    {.minFreq = 215          , .maxFreq = 270          , .limit = 30 },
    // Just for length(separatOneStr) = length(separatSixString)
    {.minFreq = 270          , .maxFreq = 700          , .limit = 30 },
    {.minFreq = 700          , .maxFreq = 800          , .limit = 30 },
    {.minFreq = 800          , .maxFreq = SPEC_FREQ_MAX, .limit = 30 } //35
};

/*
 * @brief   Splits the spectrum into groups, which has its own limit.
 *
 * @note    For six string mode!
 *
 * @note    minFreq     The start frequency of group. In Hz.
 *          maxFreq     The last frequency of group. In Hz.
 *          limit       The minimum value of the limit for finding a peak in a given group.
 */
static findPeaksSeparat separatSixStr[] = {
    {.minFreq = SPEC_FREQ_MIN, .maxFreq = 95           , .limit = 40 },
    {.minFreq = 95           , .maxFreq = 180          , .limit = 80 },
    {.minFreq = 180          , .maxFreq = 220          , .limit = 40 },
    {.minFreq = 220          , .maxFreq = 280          , .limit = 25 },
    {.minFreq = 280          , .maxFreq = 450          , .limit = 40 },
    {.minFreq = 450          , .maxFreq = SPEC_FREQ_MAX, .limit = 50 }
};

/*
 * @brief   The maximum value of the amplitude in the spectrum.
 *
 * @note    index       The position in the spectrum at which the amplitude is highest.
 *          amplitude   The value of highest peak in the spectrum.
 */
static findMaxFreq specMaxAmp = {
  .index = 0 ,
  .amplitude = 0.0
};

/*
 * @brief   Finds the smallest "limit" value in the "separations".
 *
 * @param[in]   separations     Spectrum separation params depending on the operating mode.
 *
 * @param[out]  minLimit        The smallest "limit" value in the "separations".
 *
 * @notapi
 */
float find_min_limit(findPeaksSeparat *separations){
    float minLimit = separations[0].limit;
    for (uint8_t i = 1; i < SEPARATIONS_LENGTH; i++){
        if (separations[i].limit < minLimit) minLimit = separations[i].limit; // Finds the smalest one.
    }
    return minLimit;
}

/*
 * @brief   Finds the highest peak in the spectrum and write their amplitude and index into "specMaxAmp" structure.
 *
 * @param[in]   spectrum    The pointer to the spectrum.
 *
 * @param[out]  specMaxAmp.amplitude    The amplitude of the highest peak in the spectrum.
 *
 * @note        specMaxAmp.index    A position in the spectrum at which the amplitude is highest.
 *
 * @notapi
 */
float find_spec_max_amp(float *spectrum){
    specMaxAmp.index = 0;
    specMaxAmp.amplitude = spectrum[0];
    for (uint16_t i = 1; i < SPEC_LENGTH; i++){
        if (spectrum[i] > specMaxAmp.amplitude){ // Finds the maximum one.
            specMaxAmp.amplitude = spectrum[i];
            specMaxAmp.index = i;
        }
    }
    return specMaxAmp.amplitude;
}

/*
 * @brief   Resets "peaksParams" data before starting a new cycle.
 *
 * @note    "peaksParams" structure stores their data in a static format.
 *
 * @param[in]   spectrum        The pointer to the spectrum.
 *              peaksParams     The pointer to the structure in which all data of peaks are stored.
 *
 * @notapi
 */

#include "terminal_write.h"
void peak_data_init(float *spectrum, peaksAllParams *peaksParams){
    // Clear area from 0 to 50 Hz. There are a lot of trash data.
    for (uint16_t i = 0; (i * SPEC_DF) < TRASH_DATA_LIMIT; i++)spectrum[i] = 0;
    // Clear area from 800 to SPEC_LENGTH Hz. There are a lot of trash data.
    for (uint16_t i = SPEC_LENGTH; i * SPEC_DF > 800; i--) spectrum[i] = 0;

    // Finds minimum of separation limits depending on the operating mode.
    if (MODE == SIX_STRING_MODE) {
        separationsLimitMin = find_min_limit(separatSixStr);
        nearestFreqRange = NEAREST_FREQS_RANGE_SIX_STR;
    }
    else if (MODE == ONE_STRING_MODE) {
        separationsLimitMin = find_min_limit(separatOneStr);
        nearestFreqRange = NEAREST_FREQS_RANGE_ONE_STR;
    }

    // Inits peaksParams
    for (uint8_t i = 0; i < PEAKS_MAX_LENGTH; i++) {
        peaksParams->indicesOfFreqs[i] = 0;
        peaksParams->ampOfFreqs[i] = 0;
        peaksParams->freqs[i] = 0;
    }
    peaksParams->lengthOfArrays = 0;
}

/*
 * @brief   Removes bluring of the spectrum to the right and left of the found peak.
 *
 * @note    It may not work close to start/end separations section.
 *
 * @note    Takes into account in which group of "separations" investigated frequency is.
 *
 * @param[in]   spectrum            The pointer to the spectrum.
 *              separations         Spectrum separation params depending on the operating mode.
 *              separationsIndex    The index of the section from "separations" in which the peak is located.
 *
 * @notapi
 */
void remove_bluring_of_spec(float *spectrum, findPeaksSeparat *separations, uint8_t separationsIndex){
    // It is added to the index of the hieghest peak in the spectrum.
    // Can be positive and negative. Pos - steps to the right of the peak.
    //                               Neg - steps to the left of the peak.
    int16_t indexStep;
    int16_t investigatedIndex; // The index of the hieghest peak in the spectrum plus "indexStep"
    spectrum[specMaxAmp.index] = 0;
    for (uint8_t i = 0; i < 2; i++){ // i = 0 - steps to the right. i = 1 - ... left.
        indexStep = 0; // Resets idex step because of changing direction of steps.
        while (true){
            if (i == 0) indexStep += 1; // To the right.
            else indexStep -= 1; // To the left.
            investigatedIndex = specMaxAmp.index + indexStep;
            if (investigatedIndex > SPEC_LENGTH || investigatedIndex < 0) break; //Steps is out of the spectrum range.

            if (spectrum[investigatedIndex] >= separations[separationsIndex].limit){ // Resets amplitude.
                spectrum[investigatedIndex] = 0;
            }
            else break;
        }
    }
}

/*
 * @brief   Finds indices of all peaks in the spectrum.
 *
 * @note    Finds index of a peak and removes bluring of the spectrum near that peak.
 *
 * @note    Takes into account in which group of "separations" investigated frequency is.
 *
 * @param[in]   spectrum        The pointer to the spectrum.
 *              peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              separations     Spectrum separation params depending on the operating mode.
 *
 * @param[out]  true  - We found more peaks than it should be. (PEAKS_MAX_LENGTH)
 *              false - Everything is OK. We found less peaks than it should be.
 *
 * @notapi
 */
bool find_indices_of_peaks(float *spectrum, peaksAllParams *peaksParams, findPeaksSeparat *separations){
    float investigatedFreq; // The index of the hieghest peak in the spectrum times SPEC_DF
    // If max amplitude of the spectrum is higher than minimal limit in "separations".
    while (find_spec_max_amp(spectrum) > separationsLimitMin){
        investigatedFreq = specMaxAmp.index * SPEC_DF;
        for (uint8_t i = 0; i < SEPARATIONS_LENGTH; i++){
            // Cheaks in which group of "separations" investigated frequency is located.
            if ((investigatedFreq > separations[i].minFreq) && (investigatedFreq < separations[i].maxFreq)){
                remove_bluring_of_spec(spectrum, separations, i); // Removes bluring of the spectrum to the right and left of the found peak.
                // If this peak is the required one, adds it into the structure.
                if (specMaxAmp.amplitude >= separations[i].limit){
                    peaksParams->indicesOfFreqs[peaksParams->lengthOfArrays] = specMaxAmp.index;
                    peaksParams->ampOfFreqs[peaksParams->lengthOfArrays] = specMaxAmp.amplitude;
                    peaksParams->lengthOfArrays = peaksParams->lengthOfArrays + 1;
                    if (peaksParams->lengthOfArrays == PEAKS_MAX_LENGTH) return true;
                }
                break;
            }
        }
    }
    return false;
}

/*
 * @brief   It is used by qsort function.
 *
 * @note    (a - b)     Sorts the array in ascending order.
 *          (b - a)     Sorts the array in descending order.
 *
 * @notapi
 */
int cmp(const void *a, const void *b) {
    return *(uint16_t*)a - *(uint16_t*)b;
}

/*
 * @brief   Sorts peak indices in ascending order and sorts peak amplitudes by sorting indices.
 *
 * @note    Creats two additinal arrays to hepl.
 *
 * @Exaple  index[] =     {9, 3, 7, 5, 1}
 *          amplitude[] = {1, 2, 3, 4, 5}
 *          result:
 *          index[] =     {1, 3, 5, 7, 9}
 *          amplitude[] = {5, 2, 4, 3, 1}
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *
 * @notapi
 */
void sort_amps_by_freqs(peaksAllParams *peaksParams){
    uint16_t temp_index[peaksParams->lengthOfArrays];
    float temp_amp[peaksParams->lengthOfArrays];
    // Writes data from real arrays to temp.
    for (uint16_t i = 0; i < peaksParams->lengthOfArrays; i++) {
        temp_index[i] = peaksParams->indicesOfFreqs[i];
        temp_amp[i] = peaksParams->ampOfFreqs[i];
    }
    // Sort indices.
    qsort(peaksParams->indicesOfFreqs, peaksParams->lengthOfArrays, sizeof(uint16_t), cmp);
    // Sort amplitudes by indeces.
    for (uint16_t i = 0; i < peaksParams->lengthOfArrays; i++){
        for (uint16_t j = 0; j < peaksParams->lengthOfArrays; j++){
            if (peaksParams->indicesOfFreqs[i] == temp_index[j]) peaksParams->ampOfFreqs[i] = temp_amp[j];
        }
    }
}

/*
 * @brief   Delete one frequency by the index from the array.
 *
 * @param[in]   peaksParams         The pointer to the structure in which all data of peaks are stored.
 *              deletedFreqIndex    Index of frequency in the array which needs to be deleted.
 *
 * @notapi
 */
void delete_one_freq(peaksAllParams *peaksParams, uint8_t deletedFreqIndex){
    // Shifting the array to the place of deleted index.
    for ( ; deletedFreqIndex < (peaksParams->lengthOfArrays - 1); deletedFreqIndex++){
        peaksParams->indicesOfFreqs[deletedFreqIndex] = peaksParams->indicesOfFreqs[deletedFreqIndex + 1];
        peaksParams->ampOfFreqs[deletedFreqIndex] = peaksParams->ampOfFreqs[deletedFreqIndex + 1];
        peaksParams->freqs[deletedFreqIndex] = peaksParams->freqs[deletedFreqIndex + 1];
    }
    // Resets the last index of peak.
    peaksParams->indicesOfFreqs[peaksParams->lengthOfArrays - 1] = 0;
    peaksParams->ampOfFreqs[peaksParams->lengthOfArrays - 1] = 0;
    peaksParams->freqs[peaksParams->lengthOfArrays - 1] = 0;
    peaksParams->lengthOfArrays = peaksParams->lengthOfArrays - 1;
}

/*
 * @brief   Removes nearby freqs from the array.
 *
 * @note    It takes into account the amplitude of peaks, which are lokated nearby.
 *
 * @param[in]   peaksParams         The pointer to the structure in which all data of peaks are stored.
 *
 * @notapi
 */
void delete_nearest_freqs(peaksAllParams *peaksParams){
    for (uint8_t i = 0; i < peaksParams->lengthOfArrays;){

        if (peaksParams->lengthOfArrays > (i + 1)){
            // If peaks are located nearby.
            if (peaksParams->freqs[i + 1] > peaksParams->freqs[i] &&
                peaksParams->freqs[i + 1] < peaksParams->freqs[i] + nearestFreqRange){
                // Takes into account the amplitude of peaks.
                if (peaksParams->ampOfFreqs[i] > peaksParams->ampOfFreqs[i + 1]){
                    delete_one_freq(peaksParams, (i + 1));
                }
                else delete_one_freq(peaksParams, i);
            }
            else i++;
        }
        else break;
    }
}

/*
 * @brief   Counts frequences from indices of peaks.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *
 * @notapi
 */
void count_freqs(peaksAllParams *peaksParams){
    for (uint8_t i = 0; i < peaksParams->lengthOfArrays; i++) {
        peaksParams->freqs[i] = peaksParams->indicesOfFreqs[i] * SPEC_DF;
    }
}

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
bool searchForRequiredPeaks(float *spectrum, peaksAllParams *peaksParams){
    bool flag;
    peak_data_init(spectrum, peaksParams);
    if (MODE == SIX_STRING_MODE) flag = find_indices_of_peaks(spectrum, peaksParams, separatSixStr);
    else if (MODE == ONE_STRING_MODE) flag = find_indices_of_peaks(spectrum, peaksParams, separatOneStr);

    if (flag == false){
        sort_amps_by_freqs(peaksParams);
        count_freqs(peaksParams);
        delete_nearest_freqs(peaksParams);
    }
    return flag;
}
