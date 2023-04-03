#ifndef INCLUDE_MICRO_SIGNAL_RECORDING_H_
#define INCLUDE_MICRO_SIGNAL_RECORDING_H_

#include "adc_lld.h"


// @note ADC gives values approximatly from 0 to 3100.
#define WAIT_SIGNAL_UPPER_LIMIT             3000
#define WAIT_SIGNAL_LOWER_LIMIT             50


/*
 * @brief   Record main signal after detecting a high amplitude.
 *
 * @param[in]   mainSignalBuf           An array in which data will be write from the adc.
 *              MAIN_SIGNAL_LENGTH      Number of the adc conversion which will be write to the array.
 *                                      This number is equal to lenght of input array (buf).
 */
void recordMainSignal(uint16_t *mainSignalBuf);

#endif /* INCLUDE_MICRO_SIGNAL_RECORDING_H_ */
