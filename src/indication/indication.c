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

static mailbox_t mb_indication;
static msg_t mb_indication_buf[1];


static uint16_t adc_buffer[1] = {0};

/*
 * index:
 * 		0 - string_1
 * 		1 - string_2
 * 		2 - string_3
 * 		3 - string_4
 * 		4 - string_5
 * 		5 - string_6
 * 		6 - one_string_mode
 * 		7 - six_string_mode
 */
static uint8_t diodeBuf[8] = {DIODE_NOT_ACTIVE};

static thread_t *tp_potentiometer;
static THD_WORKING_AREA(wa_potentiometer, 256);

static THD_FUNCTION(potentiometer, arg){
	chRegSetThreadName("Potentiometer");
	(void)arg;

	uint32_t potent_mode_prev = 100; // Random. Just to set initial value.
	uint32_t potent_mode_current;
	while (!chThdShouldTerminateX()){
		 adcConvert(ADC_1, &adc1_conf_13, adc_buffer, 1);

		 for (uint8_t i = 0; i < POTENT_NUM_OF_MODES; i++){
			 if (adc_buffer[0] >= i * POTENT_MODE_ADC_STEP &&
				 adc_buffer[0] < (i + 1) * POTENT_MODE_ADC_STEP){

				 potent_mode_current = i;
				 break;
			 }
		 }

		 if (potent_mode_current != potent_mode_prev){
			 potent_mode_prev = potent_mode_current;
			 chMBPostTimeout(&mb_indication, (msg_t) potent_mode_current, TIME_IMMEDIATE);
		 }

		 chThdSleepMilliseconds(500);
	}
	chThdExit(MSG_OK);
}

void set_not_active_state(void){
	for (uint8_t i = 0; i < 8; i++){
		diodeBuf[i] = DIODE_NOT_ACTIVE;
	}
}

void light_diodes(void){

	switch (diodeBuf[DIODE_ONE_STRING_MODE]){
	case DIODE_GREEN_LIGHT:
		palSetLine(ONE_STRING_MODE_LINE);
		break;
	default:
		palClearLine(ONE_STRING_MODE_LINE);
	}

	switch (diodeBuf[DIODE_SIX_STRING_MODE]){
	case DIODE_GREEN_LIGHT:
		palSetLine(SIX_STRING_MODE_LINE);
		break;
	default:
		palClearLine(SIX_STRING_MODE_LINE);
	}


	switch (diodeBuf[DIODE_STRING_1]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_1_GREEN_LINE);
		palClearLine(STRING_1_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_1_RED_LINE);
		palClearLine(STRING_1_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_1_GREEN_LINE);
		palClearLine(STRING_1_RED_LINE);
	}

	switch (diodeBuf[DIODE_STRING_2]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_2_GREEN_LINE);
		palClearLine(STRING_2_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_2_RED_LINE);
		palClearLine(STRING_2_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_2_GREEN_LINE);
		palClearLine(STRING_2_RED_LINE);
	}

	switch (diodeBuf[DIODE_STRING_3]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_3_GREEN_LINE);
		palClearLine(STRING_3_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_3_RED_LINE);
		palClearLine(STRING_3_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_3_GREEN_LINE);
		palClearLine(STRING_3_RED_LINE);
	}

	switch (diodeBuf[DIODE_STRING_4]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_4_GREEN_LINE);
		palClearLine(STRING_4_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_4_RED_LINE);
		palClearLine(STRING_4_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_4_GREEN_LINE);
		palClearLine(STRING_4_RED_LINE);
	}

	switch (diodeBuf[DIODE_STRING_5]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_5_GREEN_LINE);
		palClearLine(STRING_5_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_5_RED_LINE);
		palClearLine(STRING_5_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_5_GREEN_LINE);
		palClearLine(STRING_5_RED_LINE);
	}

	switch (diodeBuf[DIODE_STRING_6]){
	case DIODE_GREEN_LIGHT:
		palSetLine(STRING_6_GREEN_LINE);
		palClearLine(STRING_6_RED_LINE);
		break;
	case DIODE_RED_LIGHT:
		palSetLine(STRING_6_RED_LINE);
		palClearLine(STRING_6_GREEN_LINE);
		break;
	default:
		palClearLine(STRING_6_GREEN_LINE);
		palClearLine(STRING_6_RED_LINE);
	}
}

void simple_one_string_init(void){
	set_not_active_state();
	diodeBuf[DIODE_ONE_STRING_MODE] = DIODE_GREEN_LIGHT;
}

static thread_t *tp_indication;
static THD_WORKING_AREA(wa_indication, 256);

static THD_FUNCTION(indication, arg){
	chRegSetThreadName("Indication");
	(void)arg;

	msg_t msgResult;

	while (!chThdShouldTerminateX()){
		msg_t msgError = chMBFetchTimeout(&mb_indication, &msgResult, TIME_INFINITE);
		if (msgError == MSG_OK){
			switch (msgResult){
			case DIODE_STRING_1:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_1] = DIODE_RED_LIGHT;
				break;
			case DIODE_STRING_2:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_2] = DIODE_RED_LIGHT;
				break;
			case DIODE_STRING_3:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_3] = DIODE_RED_LIGHT;
				break;
			case DIODE_STRING_4:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_4] = DIODE_RED_LIGHT;
				break;
			case DIODE_STRING_5:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_5] = DIODE_RED_LIGHT;
				break;
			case DIODE_STRING_6:
				simple_one_string_init();
				diodeBuf[DIODE_STRING_6] = DIODE_RED_LIGHT;
				break;
			case DIODE_SIX_STRING_MODE:
				for (uint8_t i = 0; i < 6; i++){
					diodeBuf[i] = DIODE_RED_LIGHT;
				}
				diodeBuf[DIODE_ONE_STRING_MODE] = DIODE_NOT_ACTIVE;
				diodeBuf[DIODE_SIX_STRING_MODE] = DIODE_GREEN_LIGHT;
				break;
			default:
				set_not_active_state();
			}
		}
		chThdSleepMilliseconds(500);
	}
	chThdExit(MSG_OK);
}

void indicationInit(void){
    palSetLineMode(PAL_LINE(GPIOC, 3), PAL_MODE_INPUT_ANALOG);
    palSetLineMode(SIX_STRING_MODE_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(ONE_STRING_MODE_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(STRING_1_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(STRING_1_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(STRING_2_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_2_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_3_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_3_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_4_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_4_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_5_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_5_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_6_GREEN_LINE, PAL_MODE_OUTPUT_PUSHPULL);
	palSetLineMode(STRING_6_RED_LINE, PAL_MODE_OUTPUT_PUSHPULL);


    adcStart(ADC_1, NULL);

    chMBObjectInit(&mb_indication, mb_indication_buf, 1);

	tp_potentiometer = chThdCreateStatic(wa_potentiometer, sizeof(wa_potentiometer), NORMALPRIO, potentiometer, NULL);
	tp_indication = chThdCreateStatic(wa_indication, sizeof(wa_indication), NORMALPRIO, indication, NULL);
}
