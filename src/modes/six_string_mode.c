#include "six_string_mode.h"

// 2D array which contains freqs divided by limits (sixStringLimits).
static float freqsDecomposition[NUM_OF_STRINGS][NUM_OF_FREQS_IN_SEPARATION];
// The number of freqs in each row of "freqsDecomposition".
static uint8_t numOfElemInColom[NUM_OF_STRINGS] = {0};
// The number of first zero elements in "numOfElemInColom" + next one!
static uint8_t numOfFirstZeroElem = 0;

// The limits in which freqs of each string can be.
static sixStringLimitsParams sixStringLimits[] = {
    {.lowerLimit = 65   , .upperLimit = 96.2 }, // 6th string
    {.lowerLimit = 96.3 , .upperLimit = 128.4}, // 5th string
    {.lowerLimit = 128.5, .upperLimit = 171.4}, // 4th string
    {.lowerLimit = 171.5, .upperLimit = 221.5}, // 3rd string
    {.lowerLimit = 221.6, .upperLimit = 288.3}, // 2nd string
    {.lowerLimit = 288.4, .upperLimit = 385  }  // 1st string
};

// The dimension of "tempLimits".
static uint8_t tempLimitsLength = 0;

// Limits from "sixStringLimits" in which all freqs were deleted.
static sixStringLimitsParams tempLimits[] = {
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0}
};

/*
 * @brief   Writes zeros to "stringParams.sixStringFreqs".
 *
 * @note    Always used when some error has occurred.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 */
void writes_zeros_to_six_string_array(stringFreqsParams *stringParams){
    for (uint8_t string = 0; string < NUM_OF_STRINGS; string++){
        stringParams->sixStringFreqs[string] = 0;
    }
}

/*
 * @brief   Resets "stringParams" data and all data which is only needed for six
 *          string mode before starting a new cycle.
 *
 * @note    Resets data, which is only needed for six string mode.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void init_params_six_string(stringFreqsParams *stringParams){
    stringParams->Error = false;
    numOfFirstZeroElem = 0;
    tempLimitsLength = 0;
    writes_zeros_to_six_string_array(stringParams); // Writes zeros to stringParams.sixStringFreqs.
    stringParams->oneStringFreq = 0;
    for (uint8_t string = 0; string < NUM_OF_STRINGS; string++){
        for (uint8_t colom = 0; colom < NUM_OF_FREQS_IN_SEPARATION; colom++){
            freqsDecomposition[string][colom] = 0;
        }
        numOfElemInColom[string] = 0;
        tempLimits[string].lowerLimit = 0;
        tempLimits[string].upperLimit = 0;
    }
}

/*
 * @brief   Checks the suitability of received data from signal processing before starting.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void functionality_check(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    stringParams->Error = !((peaksParams->freqs[0] >= sixStringLimits[0].lowerLimit) &&
                            (peaksParams->freqs[0] <= sixStringLimits[NUM_OF_STRINGS - 1].upperLimit) &&
                            (peaksParams->lengthOfArrays > 1)); // In range and number of peaks is more than 1.
}

/*
 * @brief   Distributes freqs within specified limits in "sixStringLimits".
 *
 * @note    There may be freqs that aren't included in any range.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *
 * notapi
 */
void freqs_decomposition_by_limits(peaksAllParams *peaksParams){
    for (uint8_t string = 0; string < NUM_OF_STRINGS; string++){ // For each string.
        for (uint8_t peak = 0; peak < peaksParams->lengthOfArrays; peak++){ // Check all freqs.
            // In range of some separation.
            if ((peaksParams->freqs[peak] >= sixStringLimits[string].lowerLimit) &&
                (peaksParams->freqs[peak] <  sixStringLimits[string].upperLimit)){

                freqsDecomposition[string][numOfElemInColom[string]] = peaksParams->freqs[peak]; // Adds possible freq.
                numOfElemInColom[string] += 1; // Increments length of possible freqs for one string.
            }
        }
    }
}

/*
 * @brief   Checks if there is any freq which is a multiple of two investigated freq.
 *
 * @note    If there is no such freq, then it makes no sense to look for other freqs.
 *          It means that we don't have enough freqs and it is unsafe to continue processing peaks.
 *
 * @param[in]   peaksParams         The pointer to the structure in which all data of peaks are stored.
 *              stringParams        The pointer to the structure in which all data of strings are stored.
 *              investigatedFreq    The freq for which you need to find another freq that is a multiple of two.
 *
 * @notapi
 */
void multiplicity_check_six_string(peaksAllParams *peaksParams, stringFreqsParams *stringParams,
                                   float investigatedFreq){
    investigatedFreq = investigatedFreq * 2; // Double it.
    for (uint8_t peak = 0; peak < peaksParams->lengthOfArrays; peak++){ // Checks all freqs.
        if ((peaksParams->freqs[peak] <= investigatedFreq + MULT_CHECK_SIX_STR_MARGIN) &&
            (peaksParams->freqs[peak] >= investigatedFreq - MULT_CHECK_SIX_STR_MARGIN)){

            stringParams->Error = false; // We found the multiple freq.
            break;
        }
        else {
           stringParams->Error = true; // We didn't find the multiple freq.
        }
    }
}

/*
 * @brief   Finds the first real freq of string.
 *
 * @note    If in a first non-zero "numOfElemInColom" there are more than 2 element, it means
 *          that we have an extra frequency that can break everything.
 *          The only way in which first freq will be real one when we have only 1 element in
 *          a first non-zero "numOfElemInColom".
 *
 * @param[in]   peaksParams         The pointer to the structure in which all data of peaks are stored.
 *              stringParams        The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void find_first_freq(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    bool error = false; // If we need to stop a search.
    for (uint8_t string = 0; (string < NUM_OF_STRINGS) && !error; string++){
        switch (numOfElemInColom[string]){
        case 0: // Continue to look for the first freq.
            stringParams->Error = true; // If we don't find first freq it will be an error.
            break;
        case 1: // We find possible first freq.
            // Check if possible freq has doubled freq.
            multiplicity_check_six_string(peaksParams, stringParams, freqsDecomposition[string][0]);
            if (stringParams->Error == false){ // Possible freq has doubled freq.
                stringParams->sixStringFreqs[string] =  freqsDecomposition[string][0];
                numOfFirstZeroElem = string;
            }
            error = true; // Stops a search.
            break;
        default: // We have more than 2 element.
            stringParams->Error = true;
            error = true; // Stops a search.
            break;
        }
    }
}

/*
 * @brief   If all freqs were removed in the studied range, then we will not
 *          take into account the freqs that are within multiples of it.
 *
 * @note    This is necessary so that if we remove the multiple freq,
 *          then we do not accidentally find the wrong freq in the future.
 *
 * @param[in]   investigatedFreq    Investigated frequency.
 *
 * @param[out]  freqsWereLost       The investigated freq may have been a multiple of some freq.
 *
 * @notapi
 */
bool check_if_freqs_were_lost(float investigatedFreq){
    bool freqsWereLost = false; // The investigated freq is normal.
    for (uint8_t i = 0; (i < tempLimitsLength) && !freqsWereLost; i++){ // Possible starting range.
        for (uint8_t multiplier = 1; multiplier <= MAX_MULTIPLIER_FOR_LOST_FREQS; multiplier++){
        // Possible multiplied range.
            if ((investigatedFreq <= tempLimits[i].upperLimit * multiplier) &&
               (investigatedFreq >= tempLimits[i].upperLimit * multiplier)){

                freqsWereLost = true; // The investigated freq may have been a multiple of some freq.
                break;
            }
        }
    }
    return freqsWereLost;
}

/*
 * @brief   Finds all posible freqs for string exept the first one.
 *
 * @note    Be careful with this function. May lead to errors. It's a bit complicated.
 *
 * @param[in]   peaksParams         The pointer to the structure in which all data of peaks are stored.
 *              stringParams        The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void find_all_freqs_exept_first(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    bool error = false; // If we need to stop a search.
    float potentialFreq, investigatedFreqAbs;
    // If this number is greater than 2, then this is an error.
    uint8_t numOfPotentialFreq;
    bool findPossibleFreq = true; // Flag to save possible freq.

    // Explores all possible strings after the first one found.
    for (uint8_t string = 1; (string < NUM_OF_STRINGS - numOfFirstZeroElem) && !error; string++){
        // Resets data.
        potentialFreq = 0;
        numOfPotentialFreq = 0;

        // Explores all possible freqs for investigated string.
        for (uint8_t i = 0; i < numOfElemInColom[numOfFirstZeroElem + string]; i++){
            numOfPotentialFreq += 1; // Adds new potential freq.
            findPossibleFreq = true;

            // Checks if the unvestigated freq could be a multiple of another freq.
            if (check_if_freqs_were_lost(freqsDecomposition[numOfFirstZeroElem + string][i]) == false){ // It can be real freq.

                // Checks for a multiplicity of the previous real string freqs.
                for (uint8_t j = 0; j < numOfFirstZeroElem + string; j++){
                    if (stringParams->sixStringFreqs[j] != 0){
                        investigatedFreqAbs = freqsDecomposition[numOfFirstZeroElem + string][i] /
                                              stringParams->sixStringFreqs[j];

                        if ((investigatedFreqAbs <= round(investigatedFreqAbs) + FIND_ALL_FREQS_MARGIN) &&
                            (investigatedFreqAbs >= round(investigatedFreqAbs) - FIND_ALL_FREQS_MARGIN)){
                            // The investigated freq is a multiple of some previous one.
                            numOfPotentialFreq -= 1; // Removes potential freq.
                            findPossibleFreq = false; // It's not a string freq.
                            break;
                        }
                        potentialFreq = freqsDecomposition[numOfFirstZeroElem + string][i];
                    }
                }
                if (findPossibleFreq == true){ // If we find possible freq of the string.
                	potentialFreq = freqsDecomposition[numOfFirstZeroElem + string][i];
                }
            }
        }

        // Checks how many potential freqs were found.
        switch (numOfPotentialFreq){
        case 0: // Don't have potential freqs or we removed all of them.
            if (numOfElemInColom[numOfFirstZeroElem + string] != 0){ // We removed all potential freqs.
                // Adds a limit in which we might delete multiple freqs.
                tempLimits[tempLimitsLength] = sixStringLimits[numOfFirstZeroElem + string];
                tempLimitsLength += 1;
            }
            break;
        case 1: // We found a potential freq.
            // Check if possible freq has doubled freq.
            multiplicity_check_six_string(peaksParams, stringParams, potentialFreq);
            if (stringParams->Error == false){ // We found a real freq of investigated string.
                stringParams->sixStringFreqs[numOfFirstZeroElem + string] = potentialFreq;
            }
            else { // We found a noise or we lost some necessary freqs.
                writes_zeros_to_six_string_array(stringParams);
                error = true;
            }
            break;
        default: // We found more than 2 potential freqs. We found a noise.
            stringParams->Error = true;
            writes_zeros_to_six_string_array(stringParams);
            error = true;
            break;
        }
    }
}

/*
 * @brief   Prints freqsDecomposition in a terminal.
 *
 * @note    Just for debug.
 *
 * @notapi
 */
void print_freqs_decomosition(void){
    for (uint8_t colom = 0; colom < NUM_OF_STRINGS; colom++){
        if (numOfElemInColom[colom] > 0){
            for (uint8_t row = 0; row < numOfElemInColom[colom]; row++){
                dbgPrintf("%0.1f   ", freqsDecomposition[colom][row]);
            }
        }
        else dbgPrintf("0.0     ");
        dbgPrintf("\r\n");
    }
}

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
void sixStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    init_params_six_string(stringParams);
    functionality_check(peaksParams, stringParams);
    if (stringParams->Error == false){
        freqs_decomposition_by_limits(peaksParams);
        //print_freqs_decomosition();
        find_first_freq(peaksParams, stringParams);
        if (stringParams->Error == false){
            find_all_freqs_exept_first(peaksParams, stringParams);
        }
        else writes_zeros_to_six_string_array(stringParams);
    }
    else writes_zeros_to_six_string_array(stringParams);
}
