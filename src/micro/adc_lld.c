#include "adc_lld.h"

/*
 * @brief   Setting the timer configuration to start the adc conversion with some period.
 *
 * @note    The timer makes the TRGO event which is used to start the adc conversion.
 *
 * @note    It helps starting the adc conversion with some frequency.
 *
 * @note    GPTD3 is used.
 */
static const GPTConfig tim3_conf = {
    .frequency = (gptfreq_t) GPT_CONFIG_FREQUENCY, // Sets the timer frequency.
    .callback = NULL,
    .cr2 = TIM_CR2_MMS_1, // Sets the TRGO events.
    .dier = 0
};

/*
 * @brief   Setting the adc configuration.
 *
 * @note    The ADC conversion is started by the timer.
 *
 * @note    ADC1 is used.
 *
 * @note    The channel 0 from the ADC1 is used.
 */
static ADCConversionGroup adc0_conf = {
    .circular = false, // Non-continuous mode.

    .num_channels = 1, // Used only one channel.

    .end_cb = NULL,
    .error_cb = NULL,

    .cr1 = 0,
    .cr2 = ADC_CR2_EXTEN_RISING | ADC_CR2_EXTSEL_SRC(0b0100), // Sets the TRGO event.

    .smpr1 = ADC_SMPR1_SMP_AN10(ADC_SAMPLE_144),
    .smpr2 = 0, // 239.5 cycles sampling time.

    .sqr1 = 0, // Number of channels.
    .sqr2 = 0,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN10) // Which channel is used.
};

/*
 * @brief   Inits the adc conversion by the timer and sets the leg to analog mode.
 *
 * @note    ADC1 is used.
 *
 * @note    The channel 0 from the ADC1 is used.
 *
 * @note    GPTD3 is used.
 */
void adcSimpleInit(void){
    gptStart(GPT_3, &tim3_conf);
    adcStart(ADC_1, NULL);
    palSetLineMode(PAL_LINE(GPIOC, 0), PAL_MODE_INPUT_ANALOG);
    gptStartContinuous(GPT_3, (gptcnt_t) GPT_PERIOD);
}

/*
 * @brief   Stops timer and ADC.
 *
 * @note    ADC1 is used.
 *
 * @note    GPTD3 is used.
 */
void adcSimpleUninit(void){
    gptStop(GPT_3);
    adcStop(ADC_1);
}

/*
 * @bried       Reads data from the ADC and writes it to the array.
 *
 * @note    ADC1 is used.
 *
 * @note    GPTD3 is used.
 *
 * @param[in]   buf               An array in which data will be write from the adc.
 *
 * @note        numberOfSamples   Number of the adc conversion which will be write to the array.
 *                                This number is equal to lenght of input array (buf).
 */
void adcSimpleRead(uint16_t *buf, uint16_t numberOfSamples){
    adcConvert(ADC_1, &adc0_conf, buf, numberOfSamples);
}


