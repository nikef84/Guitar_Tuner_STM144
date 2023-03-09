#ifndef INCLUDE_FINDPEAKS_POWER_FFT_H_
#define INCLUDE_FINDPEAKS_POWER_FFT_H_

#include "common.h"


#define REDUCE_AVERAGE_LEVEL_TO_ZERO        1533
/*
 * @brief   Makes the FFT of the signal and returns the spec of this signal.
 *
 * @note    It works like in Labview.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error here.
 *
 * @param[in]   spectrum    Result of FFT.
 *              signal      Array of real numbers with which we will calculate the FFT.
 */
void fft(float *spectrum, uint16_t *signal);

#endif /* INCLUDE_FINDPEAKS_POWER_FFT_H_ */
