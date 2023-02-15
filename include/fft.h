#ifndef INCLUDE_FFT_H_
#define INCLUDE_FFT_H_

#include "math.h"
#include "common.h"

// @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error.
#define SIGNAL_LENGTH           8192

/*
 * @brief   Makes the FFT of the signal and returns the spec of this signal.
 *
 * @note    It works like in Labview.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error here.
 *
 * @param[in]   spec        Result of FFT.
 *              signal      Array of real numbers with which we will calculate the FFT.
 */
void fft(float *spec, uint16_t *signal);

#endif /* INCLUDE_FFT_H_ */
