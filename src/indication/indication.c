#include "indication.h"

// Permission to get new values to the potentiometer.
static bool potentPermission = true;
// The current operating mode of the program.
static uint8_t operatingMode = ONE_STRING_MODE;
// The current string that we are tuning in ONE_STRING_MODE.
static uint8_t currentString = 1;
// The current value of the potentiometer.
static uint16_t adc_buffer[POTENT_ADC_BUF] = {0};

// The mailbox that stores instructions for the operation of LEDs.
static mailbox_t mb_indication;
static msg_t mb_indication_buf[POTENT_MB_BUF];

// The tread in which the value from the potentiometer is read.
static thread_t *tp_potentiometer;
static THD_WORKING_AREA(wa_potentiometer, 256);
// The tread that controls the LEDs.
static thread_t *tp_indication;
static THD_WORKING_AREA(wa_indication, 256);

/*
 * @brief	The current state of the LEDs.
 *
 * @note 	From 0 to 5 indices, the value can be from 0 to 2.
 * 			6 and 7 indices, the value can be 0 or 1.
 *
 * @note	index:
 * 				0 - string_1
 * 				1 - string_2
 * 				2 - string_3
 * 				3 - string_4
 * 				4 - string_5
 * 				5 - string_6
 * 				6 - six_string_mode
 * 				7 - one_string_mode
 */
static uint8_t ledBuf[NUM_OF_LEDS] = {LED_NOT_ACTIVE};
// New values for the LEDs. Can be from 0 to 2. Sets into "ledBuf[0-5]".
static uint8_t ledNewString[NUM_OF_STRING] = {0};

/*
 * @brief	Stores the LED leg ports that are responsible for the strings.
 *
 * @note	First row is GREEN, second - RED.
 * 			Coloms are strings.
 */
static uint32_t ledLegs [2][NUM_OF_STRING] = {{STRING_1_GREEN_LINE, STRING_2_GREEN_LINE,
												 STRING_3_GREEN_LINE, STRING_4_GREEN_LINE,
												 STRING_5_GREEN_LINE, STRING_6_GREEN_LINE},
												{STRING_1_RED_LINE, STRING_2_RED_LINE,
												 STRING_3_RED_LINE, STRING_4_RED_LINE,
												 STRING_5_RED_LINE, STRING_6_RED_LINE}};
/*
 * @brief   Setting the adc configuration (potentiometer).
 *
 * @note    ADC1 is used.
 *
 * @note    The channel 13 from the ADC1 is used.
 */
ADCConversionGroup adc1_conf_13 = {

    .circular = FALSE, // Non-continuous mode.

    .num_channels = 1, // Used only one channel.

    .end_cb = NULL,
    .error_cb = NULL,

    .cr1 = 0,
    .cr2 = ADC_CR2_SWSTART, // Start Conversion of regular channels.

    .smpr1 = ADC_SMPR1_SMP_AN13(ADC_SAMPLE_144),
    .smpr2 = 0,

    .htr = 0,
    .ltr = 0,

    .sqr1 = 0,
    .sqr2 = 0,
    .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN13) // Which channel is used.
};

/*
 * @brief	Turns off all LEDs.
 *
 * @notapi
 */
void set_not_active_state(void){
	for (uint8_t i = 0; i < NUM_OF_LEDS; i++){
		ledBuf[i] = LED_NOT_ACTIVE;
	}
	for (uint8_t i = 0; i < NUM_OF_STRINGS; i++){
		ledNewString[i] = LED_NOT_ACTIVE;
	}
}

/*
 * @brief	Lights the LEDs depending on the values in the "ledBuf".
 *
 * @note	LED_ONE_STRING_MODE and LED_SIX_STRING_MODE can only light green.
 * 			The rest can light both green and red.
 *
 * @notapi
 */
void light_diodes(void){

	// Lights LED_ONE_STRING_MODE.
	switch (ledBuf[LED_ONE_STRING_MODE]){
	case LED_GREEN_LIGHT:
		palSetLine(ONE_STRING_MODE_LINE);
		break;
	default:
		palClearLine(ONE_STRING_MODE_LINE);
	}
	// Lights LED_SIX_STRING_MODE.
	switch (ledBuf[LED_SIX_STRING_MODE]){
	case LED_GREEN_LIGHT:
		palSetLine(SIX_STRING_MODE_LINE);
		break;
	default:
		palClearLine(SIX_STRING_MODE_LINE);
	}

	// Lights the LEDs that are responsible for the strings.
	for (uint8_t i = 0; i < NUM_OF_STRING; i++){
		switch (ledBuf[i]){
			case LED_GREEN_LIGHT:
				palSetLine(ledLegs[GREEN][i]);
				palClearLine(ledLegs[RED][i]);
				break;
			case LED_RED_LIGHT:
				palSetLine(ledLegs[RED][i]);
				palClearLine(ledLegs[GREEN][i]);
				break;
			default:
				palClearLine(ledLegs[GREEN][i]);
				palClearLine(ledLegs[RED][i]);
			}
	}
}

/*
 * @brief	The tread in which the value from the potentiometer is read.
 *
 * @note	Divides the value from the potentiometer into 7 values.
 * 			From 0 to 5 - string with we want to tune.
 * 			6 - SIX_STRING_MODE.
 *
 * @note	Sends data to the indication thread by the mailbox.
 */
static THD_FUNCTION(potentiometer, arg){
	chRegSetThreadName("Potentiometer");
	(void)arg;

	uint8_t potent_mode_prev = 100; // Random. Just to set the initial value.
	uint8_t potent_mode_current;
	while (!chThdShouldTerminateX()){
		if (potentPermission == true){ // If it is allowed to read a new data.
			adcConvert(ADC_1, &adc1_conf_13, adc_buffer, POTENT_ADC_BUF);
			// Divides the value from the potentiometer into 7 values.
			for (uint8_t i = 0; i < POTENT_NUM_OF_MODES; i++){
				if (adc_buffer[0] >= i * POTENT_MODE_ADC_STEP &&
						adc_buffer[0] < (i + 1) * POTENT_MODE_ADC_STEP){

					potent_mode_current = i;
					break;
				}
			}

			// If the operating mode has changed, then send a new value to the indication thread.
			if (potent_mode_current != potent_mode_prev){
				potent_mode_prev = potent_mode_current;
				chMBPostTimeout(&mb_indication, (msg_t) potent_mode_current, TIME_IMMEDIATE);
			}
		}

		chThdSleepMilliseconds(POTENT_READ_PERIOD);
	}
	chThdExit(MSG_OK);
}

/*
 * @brief	The tread that controls the LEDs.
 *
 * @note	Waits for the msg by the mailbox and then starts to control the LEDs.
 * 			The msg indicates that new values have arrived.
 */
static THD_FUNCTION(indication, arg){
	chRegSetThreadName("Indication");
	(void)arg;

	msg_t msgResult; // The msg from the mailbox.

	while (!chThdShouldTerminateX()){
		// Wait for the msg.
		msg_t msgError = chMBFetchTimeout(&mb_indication, &msgResult, TIME_INFINITE);
		if (msgError == MSG_OK){
			uint8_t result = (uint8_t) msgResult;
			// If we have changed the string we want to tune. Only from the potentiometer!
			if (result < NUM_OF_STRING){
				set_not_active_state();
				ledBuf[LED_ONE_STRING_MODE] = LED_GREEN_LIGHT;
				ledBuf[LED_SIX_STRING_MODE] = LED_NOT_ACTIVE;
				operatingMode = ONE_STRING_MODE;

				ledBuf[result] = LED_RED_LIGHT;
				ledNewString[result] = LED_RED_LIGHT;
				currentString = result + 1;
			}
			else {
				switch (msgResult){
				// If we have changed the operationg mode. Only from the potentiometer.
				case LED_SIX_STRING_MODE:
					for (uint8_t i = 0; i < NUM_OF_STRING; i++){
						ledBuf[i] = LED_RED_LIGHT;
						ledNewString[i] = LED_RED_LIGHT;
					}
					ledBuf[LED_ONE_STRING_MODE] = LED_NOT_ACTIVE;
					ledBuf[LED_SIX_STRING_MODE] = LED_GREEN_LIGHT;
					operatingMode = SIX_STRING_MODE;
					currentString = 0;
					break;

				// If we have new values for the LEDs.
				case LED_NEW_STRING_VALUE:
					for (uint8_t i = 0; i < NUM_OF_STRING; i++){
						if (ledBuf[i] != LED_GREEN_LIGHT){
							ledBuf[i] = ledNewString[i];
						}
					}
//					if (operatingMode == SIX_STRING_MODE){
//
//					}
//					else if (operatingMode == ONE_STRING_MODE){
//						for (uint8_t i = 0; i < NUM_OF_STRING; i++){
//							ledBuf[i] = ledNewString[i];
//						}
//					}
					break;

				// If we want to reset LEDs. Turns of all green lights.
				case LED_RESET:
					if (operatingMode == SIX_STRING_MODE){
						for (uint8_t i = 0; i < NUM_OF_STRING; i++){
							ledBuf[i] = LED_RED_LIGHT;
							ledNewString[i] = LED_RED_LIGHT;
						}
					}
					else if (operatingMode == ONE_STRING_MODE){
						for (uint8_t i = 0; i < NUM_OF_STRING; i++){
							ledBuf[i] = LED_NOT_ACTIVE;
							ledNewString[i] = LED_NOT_ACTIVE;
						}
						ledBuf[currentString] = LED_RED_LIGHT;
						ledNewString[currentString] = LED_RED_LIGHT;
					}
					break;

				// If we want to turn off all LEDs.
				case LED_TURN_OFF:
					set_not_active_state();
					break;

				// If we got incorrect msg.
				default:
					set_not_active_state();
				}
			}

			light_diodes();
		}
		//chThdSleepMilliseconds(INDICATION_PERIOD);
	}
	chThdExit(MSG_OK);
}

/*
 * @brief	Inits indication.
 *
 * @note	Sets legs, starts ADC, mailbox and threads.
 *
 * @note 	ADC1 CH13 is used.
 */
void indicationInit(void){
	// Sets the leg for the potentiometer..
    palSetLineMode(POTENT_LINE, PAL_MODE_INPUT_ANALOG);

    // Sets legs for the LEDs.
    for (uint8_t i = 0; i < NUM_OF_STRING; i++){
        palSetLineMode(ledLegs[GREEN][i], PAL_MODE_OUTPUT_PUSHPULL);
        palSetLineMode(ledLegs[RED][i], PAL_MODE_OUTPUT_PUSHPULL);
    }
    palSetLineMode(SIX_STRING_MODE_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(ONE_STRING_MODE_LINE, PAL_MODE_OUTPUT_PUSHPULL);

    // Start ADC.
    adcStart(ADC_1, NULL);

    // Inits the mailbox.
    chMBObjectInit(&mb_indication, mb_indication_buf, 1);

    //Starts threads.
	tp_potentiometer = chThdCreateStatic(wa_potentiometer, sizeof(wa_potentiometer), NORMALPRIO, potentiometer, NULL);
	tp_indication = chThdCreateStatic(wa_indication, sizeof(wa_indication), NORMALPRIO, indication, NULL);
}

/*
 * @brief	Sets permission to get new values to the potentiometer.
 *
 * @param[in]	permission	New permission for the potentiometer.
 */
void setPotentPermission(bool permission){
	potentPermission = permission;
}

/*
 * @brief	Gets the current value of the permission to get new values to the potentiometer.
 *
 * @param[out]		The current value of the permission for the potentiometer.
 */
bool getPotentPermission(void){
	return potentPermission;
}

/*
 * @brief	Sets new value of the operating mode.
 *
 * @param[in]	newOperatingMode	New value of the operating mode.
 */
void setOperatingMode(uint8_t newOperatingMode){
	operatingMode = newOperatingMode;
}

/*
 * @brief	Gets the current value of the operating mode.
 *
 * @param[out]		The current value of the operating mode.
 */
uint8_t getOperatingMode(void){
	return operatingMode;
}

/*
 * @brief	Sets new value of the string that we want to tune.
 *
 * @param[in]	newCurrentString	New value of the string that we want to tune.
 */
void setCurrentString(uint8_t newCurrentString){
	currentString = newCurrentString;
}

/*
 * @brief	Gets the current value of the string that we want to tune.
 *
 * @param[out]		The current value of the string that we want to tune.
 */
uint8_t getCurrentString(void){
	return currentString;
}

/*
 * @brief	Sets new values to the string LEDs.
 *
 * @note 	Sends the msg to the mailbox that we have new values for LEDs.
 *
 * @param[in]	newValue		New value to the string LED.
 * 				numOfString		The string number of which we need to change the value.
 */
void setStringLeds(uint8_t newValue, uint8_t numOfString){
	if (operatingMode == ONE_STRING_MODE && newValue == LED_RED_LIGHT) newValue = LED_NOT_ACTIVE;
	ledNewString[numOfString - 1] = newValue;
	chMBPostTimeout(&mb_indication, (msg_t) LED_NEW_STRING_VALUE, TIME_IMMEDIATE);
}

/*
 * @brief	Resets the string LEDs to inital values.
 */
void resetsLeds(void){
	chMBPostTimeout(&mb_indication, (msg_t) LED_RESET, TIME_IMMEDIATE);
}

/*
 * @brief	Turns off all LEDs.
 */
void turnOffAllLeds(void){
	chMBPostTimeout(&mb_indication, (msg_t) LED_TURN_OFF, TIME_IMMEDIATE);
}

/*
 * @brief	Checks the number of LEDs that are green depending on the operating mode.
 *
 * @param[out]		True - all LEDs depending on the operating mode are green.
 */
bool checkNeedToResetLeds(void){
	bool flag;
	if (operatingMode == SIX_STRING_MODE){
		for (uint8_t i = 0; i < NUM_OF_STRING; i++){
			if (ledBuf[i] != LED_GREEN_LIGHT){
				flag = false;
				break;
			}
			else flag = true;
		}
	}
	else if (operatingMode == ONE_STRING_MODE){
		for (uint8_t i = 0; i < NUM_OF_STRING; i++){
			if (ledBuf[i] == LED_GREEN_LIGHT){
				flag = true;
				break;
			}
			else flag = false;
		}
	}
	return flag;
}
