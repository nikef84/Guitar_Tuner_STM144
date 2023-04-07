#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

/*
 * @brief   Timer operation parameters.
 *
 * @note    It is used in adc_lld.h.
 */
#define GPT_CONFIG_FREQUENCY                2000000.0
#define GPT_PERIOD                          500.0


/*
 * @brief   Signal and FFT parameters.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error.
 *
 * @note    It is used in signal_recording.h and fft.h.
 */
#define MAIN_SIGNAL_LENGTH                  8192 // 8192
#define SPEC_LENGTH                         MAIN_SIGNAL_LENGTH / 2
#define MAIN_SIGNAL_DT                      GPT_PERIOD / GPT_CONFIG_FREQUENCY
#define SPEC_DF                             1 / (MAIN_SIGNAL_DT * MAIN_SIGNAL_LENGTH)
#define WAIT_SIGNAL_SAMPLES                 50

/*
 * @brief   Peaks parametres.
 *
 * @note    It is used in findPeaks.h.
 */
#define PEAKS_MAX_LENGTH                    100


typedef struct{
    float ampOfFreqs[PEAKS_MAX_LENGTH];
    uint8_t lengthOfArrays;
    float freqs[PEAKS_MAX_LENGTH];
} peaksAllParams;

typedef struct{
	float result[6];
    float sixStringFreqs[6];
    float oneStringFreq;
    bool Error;
} stringFreqsParams;

// @brief   Possible operating modes of the program.
#define SIX_STRING_MODE                     0
#define ONE_STRING_MODE                     1

// The current operating mode of the program.
#define MODE                                SIX_STRING_MODE

// Number of strings.
#define NUM_OF_STRINGS                      6

// String numbers.
#define STRING_1							1
#define STRING_2							2
#define STRING_3							3
#define STRING_4							4
#define STRING_5							5
#define STRING_6							6

// The string that we are tuning in ONE_STRING_MODE.
#define STRING								STRING_2

#endif /* INCLUDE_SETTINGS_H_ */
