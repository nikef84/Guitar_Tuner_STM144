#ifndef INCLUDE_MICRO_ADC_LLD_H_
#define INCLUDE_MICRO_ADC_LLD_H_

#include "common.h"


// @brief   Which timer and adc is used.
#define GPT_5                       &GPTD5
#define ADC_1                       &ADCD1
#define ADC_LINE_CH0                PAL_LINE(GPIOA, 0)

/*
 * @brief   Inits the adc conversion by the timer and sets the leg to analog mode.
 *
 * @note    ADC1 is used.
 *
 * @note    The channel 0 from the ADC1 is used.
 *
 * @note    GPTD5 is used.
 */
void adcSimpleInit(void);

/*
 * @brief   Stops timer and ADC.
 *
 * @note    ADC1 is used.
 *
 * @note    GPTD5 is used.
 */
void adcSimpleUninit(void);


/*
 * @bried       Reads data from the ADC and writes it to the array.
 *
 * @note    ADC1 is used.
 *
 * @note    GPTD5 is used.
 *
 * @param[in]   buf               An array in which data will be write from the adc.
 *
 * @note        numberOfSamples   Number of the adc conversion which will be write to the array.
 *                                This number is equal to lenght of input array (buf).
 */
void adcSimpleRead(uint16_t *buf, uint16_t numberOfSamples);


#endif /* INCLUDE_MICRO_ADC_LLD_H_ */
