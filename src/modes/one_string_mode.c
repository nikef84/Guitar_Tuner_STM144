#include "one_string_mode.h"

// An array which includes difference between nearest freqs.
static float diffFreqs[DIFF_FREQS_LENGTH] = {0};
static uint8_t diffFreqsLength = 0;

/*
 * @brief   Resets "stringParams" data before starting a new cycle.
 *
 * @note    "stringParams" structure stores their data in a static format.
 *
 * @param[in]   stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void init_params_one_string(stringFreqsParams *stringParams){
    for (uint8_t i = 0; i < (DIFF_FREQS_LENGTH); i++) diffFreqs[i] = 0;
    writes_zeros_to_six_string_array(stringParams);
    for (uint8_t string; string < NUM_OF_STRINGS; string++){
    	stringParams->result[string] = 0;
    }
    stringParams->oneStringFreq = 0;
    stringParams->Error = false;
}

/*
 * @brief   Checks that all freqs are multiples of half the first.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void multiplicity_check_one_string(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    float halfOfFirstPeak = peaksParams->freqs[0] / 2;
    float investigatedFreqAbs;
    for (uint8_t i = 1; i < peaksParams->lengthOfArrays; i++){
        investigatedFreqAbs = peaksParams->freqs[i] / halfOfFirstPeak;
        if (investigatedFreqAbs <= (round(investigatedFreqAbs) + MULT_CHECK_ONE_STR_MARGIN) &&
            investigatedFreqAbs >= (round(investigatedFreqAbs) - MULT_CHECK_ONE_STR_MARGIN)){
            stringParams->Error = false; // Evrything is OK.
        }
        else {
            stringParams->Error = true; // Found some extra peaks.
            break;
        }
    }
}

/*
 * @brief   It is used by qsort function.
 *
 * @note    (a - b)     Sorts the array in ascending order.
 *          (b - a)     Sorts the array in descending order.
 *
 * @notapi
 */
static int qfloat(const void *pa, const void *pb) {
    float a = *(float*)pa, b = *(float*)pb;
    if (a > b) return 1;
    if (a < b) return -1;
    return 0;
}

/*
 * @brief   Calculates difference between nearest freqs.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void nearest_freqs_diff(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    if (stringParams->Error == false){ // Evrything is OK.
        for (uint8_t i = 0; i < (peaksParams->lengthOfArrays - 1); i++) {
            diffFreqs[i] = peaksParams->freqs[i + 1] - peaksParams->freqs[i];
            diffFreqsLength = diffFreqsLength + 1;
        }
        qsort(diffFreqs, diffFreqsLength, sizeof(float), qfloat); // Sorts an array.
    }
    else stringParams->oneStringFreq = 0; // We got an error before.
}

/*
 * @brief   Checks the possibility that we caught the noise at a multiple frequency.
 *
 * @note    Writes a possible freq to "stringParams->oneStringFreq".
 *
 * @note    MULTIPLY_NOISE_CHECK_LIMIT      Limit to check if we have a multiply noise.
 *
 * @Example     array = {100, 300, 600}
 *              diif  = {200, 300}
 *              300 / 100 = 3 > 2.1 then 100 - a multiply noise.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void multiply_noise_check(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    if (stringParams->Error == false){ // Evrything is OK.
        if ((diffFreqs[diffFreqsLength - 1] / peaksParams->freqs[0]) >= MULTIPLY_NOISE_CHECK_LIMIT){
            // We caught a noise.
            stringParams->oneStringFreq = 0;
            stringParams->Error = true;
        }
        else { // Evrything is OK.
            stringParams->oneStringFreq = diffFreqs[0];
            stringParams->Error = false;
        }

    }
    else stringParams->oneStringFreq = 0; // We got an error before.
}

/*
 * @brief   Finds a real freq of one string.
 *
 * @note    If the "stringParams->oneStringFreq" is "0", then we had an error.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
void find_real_freq(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    if (stringParams->Error == false){ // Evrything is OK.
        if (stringParams->oneStringFreq <= (peaksParams->freqs[0] + FIND_REAL_FREQ_MARGIN) &&
            stringParams->oneStringFreq >= (peaksParams->freqs[0] - FIND_REAL_FREQ_MARGIN)){

            stringParams->oneStringFreq = peaksParams->freqs[0];
        }
        else {
            if (peaksParams->freqs[0] < stringParams->oneStringFreq) {
                stringParams->oneStringFreq = peaksParams->freqs[0];
            }
            // If not then stringParams->oneStringFreq = diffFreqs[0].
        }
    }
    else stringParams->oneStringFreq = 0; // We got an error before.
}

/*
 * @brief	Writes data from oneStringFreq to result.
 *
 * @note 	Just to make it easier to control servos. Because of ONE_STRING_MODE.
 *
 * @param[in]   stringParams        The pointer to the structure in which all data of strings are stored.
 *
 * @notapi
 */
static void write_to_result(stringFreqsParams *stringParams){
	if (stringParams->Error == false){
		stringParams->result[getCurrentString() - 1] = stringParams->oneStringFreq;
	}
}

/*
 * @brief   Checks if the received data is correct and finds a real freq of one string.
 *
 * @note    If the "stringParams->oneStringFreq" is "0", then we had an error.
 *
 * @param[in]   peaksParams     The pointer to the structure in which all data of peaks are stored.
 *              stringParams    The pointer to the structure in which all data of strings are stored.
 */
void oneStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    if (peaksParams->lengthOfArrays > 1){
        init_params_one_string(stringParams);
        multiplicity_check_one_string(peaksParams, stringParams);
        nearest_freqs_diff(peaksParams, stringParams);
        multiply_noise_check(peaksParams, stringParams);
        find_real_freq(peaksParams, stringParams);
        write_to_result(stringParams);
    }
    else {
        stringParams->Error = true;
        stringParams->oneStringFreq = 0;
    }
}

