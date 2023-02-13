#include "fft.h"
#include "terminal_write.h"
#include "adc_lld.h"

#define ARRAY_LENGTH        5000
static uint16_t array_re[ARRAY_LENGTH] = {0};
static uint16_t array[ARRAY_LENGTH] = {1};
//static uint16_t array_re[ARRAY_LENGTH] = {1, 2, 3, 5, 5, 6, 7, 8};
//static float array_im[ARRAY_LENGTH] = {0};

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


void fft_test(void){

    halInit();
    chSysInit();
    debugStreamInit();
    dbgPrintf("Start\r\n");
    adcSimpleInit();
    for (uint16_t i = 0; i < ARRAY_LENGTH; i++){
        array[i] = i;
    }
    adcConvert(&ADCD1, &adc0_conf, array_re, 5000);
//    fft(array_re, array_im, ARRAY_LENGTH);
    while (true){
      dbgPrintf("%d    \r\n", array_re[3]);
      dbgPrintf("%d    \r\n", array[4000]);
      chThdSleepMilliseconds(100000);
    }
}
