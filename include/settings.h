#ifndef INCLUDE_SETTINGS_H_
#define INCLUDE_SETTINGS_H_

/*
 * @brief   Timer operation parameters.
 *
 * @note    It is used in adc_lld.h.
 */
#define GPT_CONFIG_FREQUENCY                2000000.0
#define GPT_PERIOD                          1000.0


/*
 * @brief   Signal and FFT parameters.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error.
 *
 * @note    It is used in signal_recording.h and fft.h.
 */
#define MAIN_SIGNAL_LENGTH                  2048 // 8192
#define SPEC_LENGTH                         MAIN_SIGNAL_LENGTH / 2
#define MAIN_SIGNAL_DT                      GPT_PERIOD / GPT_CONFIG_FREQUENCY
#define SPEC_DF                             1 / (MAIN_SIGNAL_DT * MAIN_SIGNAL_LENGTH)
#define WAIT_SIGNAL_NUMBER_OF_SAMLES        50

/*
 * @brief   Peaks parametres.
 *
 * @note    It is used in findPeaks.h.
 */
#define PEAKS_MAX_LENGTH                    50


typedef struct{
    uint16_t indicesOfFreqs[PEAKS_MAX_LENGTH];
    float ampOfFreqs[PEAKS_MAX_LENGTH];
    uint8_t lengthOfArrays;
    float freqs[PEAKS_MAX_LENGTH];
} peaksAllParams;





#endif /* INCLUDE_SETTINGS_H_ */
