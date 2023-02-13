#ifndef INCLUDE_SIGNAL_RECORDING_H_
#define INCLUDE_SIGNAL_RECORDING_H_

#include "adc_lld.h"

#define WAIT_SIGNAL_NUMBER_OF_SAMLES        50
// @note ADC gives values approximatly from 0 to 3300.
#define WAIT_SIGNAL_UPPER_LIMIT             2500
#define WAIT_SIGNAL_LOWER_LIMIT             500


/*
 * @brief   Record main signal after detecting a high amplitude.
 *
 * @param[in]   mainSignalBuf       An array in which data will be write from the adc.
 *              numberOfSamples     Number of the adc conversion which will be write to the array.
 *                                  This number is equal to lenght of input array (buf).
 *                                  This number MUST be less than 7000!
 */
void recordMainSignal(uint16_t *mainSignalBuf, uint16_t numberOfSamples);

#endif /* INCLUDE_SIGNAL_RECORDING_H_ */
