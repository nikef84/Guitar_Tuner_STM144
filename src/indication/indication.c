#include "indication.h"

ADCConversionGroup adc1_conf_13 = {

    .circular = FALSE,

    .num_channels = 1,

    .end_cb = NULL,
    .error_cb = NULL,

    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART,

    .smpr1 = ADC_SMPR1_SMP_AN13(ADC_SAMPLE_144),
    .smpr2 = 0,

    .htr = 0,
    .ltr = 0,

    .sqr1 = 0,
    .sqr2 = 0,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN13)
};

static uint16_t adc_buffer[1] = {0};

static thread_t *tp_potentiometer;

static THD_WORKING_AREA(wa_potentiometer, 256);

static THD_FUNCTION(potentiometer, arg){
	chRegSetThreadName("Potentiometer");
	(void)arg;

	uint8_t	potent_mode_prev = 100; // Random. Just to set initial value.
	uint8_t potent_mode_current;
	while (!chThdShouldTerminateX()){
		 adcConvert(ADC_1, &adc1_conf_13, adc_buffer, 1);

		 for (uint8_t i = 0; i < POTENT_NUM_OF_MODES; i++){
			 if (adc_buffer[0] >= i * POTENT_MODE_ADC_STEP &&
				 adc_buffer[0] < (i + 1) * POTENT_MODE_ADC_STEP){

				 potent_mode_current = i + 1;
				 break;
			 }
		 }

		 if (potent_mode_current != potent_mode_prev){
			 potent_mode_prev = potent_mode_current;
			 dbgPrintf("mode = %d\r\n", potent_mode_current);
		 }

		 chThdSleepMilliseconds(500);
	}
	chThdExit(MSG_OK);
}

void indicationInit(void){
    palSetLineMode(PAL_LINE(GPIOC, 3), PAL_MODE_INPUT_ANALOG);
    adcStart(ADC_1, NULL);
	tp_potentiometer = chThdCreateStatic(wa_potentiometer, sizeof(wa_potentiometer), NORMALPRIO, potentiometer, NULL);
}
