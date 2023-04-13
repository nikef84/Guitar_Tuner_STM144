#ifndef INCLUDE_INDICATION_INDICATION_H_
#define INCLUDE_INDICATION_INDICATION_H_

#include "common.h"
#include "adc_lld.h"

// Potentiometer.
// To divide adc value to groups (modes).
#define POTENT_MODE_ADC_STEP			586
#define POTENT_MODE_ADC_MIN				0
#define POTENT_MODE_ADC_MAX				4096

// The number of the potentiometer modes.
#define POTENT_NUM_OF_MODES				7

// Potentiometer ADC.
#define POTENT_LINE						PAL_LINE(GPIOC, 3)
#define POTENT_ADC_BUF					1
#define POTENT_MB_BUF					1

//The period for reading values from the potentiometer.
#define POTENT_READ_PERIOD				100 // ms.

// LEDs.
// LEDs legs.
#define SIX_STRING_MODE_LINE			PAL_LINE(GPIOF, 9)
#define ONE_STRING_MODE_LINE			PAL_LINE(GPIOF, 7)
#define STRING_1_GREEN_LINE				PAL_LINE(GPIOC, 8)
#define STRING_1_RED_LINE				PAL_LINE(GPIOC, 9)
#define STRING_2_GREEN_LINE				PAL_LINE(GPIOC, 11)
#define STRING_2_RED_LINE				PAL_LINE(GPIOC, 12)
#define STRING_3_GREEN_LINE				PAL_LINE(GPIOG, 2)
#define STRING_3_RED_LINE				PAL_LINE(GPIOG, 3)
#define STRING_4_GREEN_LINE				PAL_LINE(GPIOD, 6)
#define STRING_4_RED_LINE				PAL_LINE(GPIOD, 5)
#define STRING_5_GREEN_LINE				PAL_LINE(GPIOE, 2)
#define STRING_5_RED_LINE				PAL_LINE(GPIOE, 4)
#define STRING_6_GREEN_LINE				PAL_LINE(GPIOE, 6)
#define STRING_6_RED_LINE				PAL_LINE(GPIOE, 3)

// LEDs possible values for ledBuf.
#define LED_NOT_ACTIVE					0
#define LED_GREEN_LIGHT					1
#define LED_RED_LIGHT					2

// The number of LEDs.
#define NUM_OF_LEDS						8

// Indices of possible msgs.
#define LED_SIX_STRING_MODE				6
#define LED_ONE_STRING_MODE				7
#define LED_NEW_STRING_VALUE			10
#define LED_RESET						15
#define LED_TURN_OFF					27

// Just for normal use ledLegs[].
#define GREEN							0
#define RED								1

// The period for checking new msgs in the mailbox.
#define INDICATION_PERIOD				100

/*
 * @brief	Inits indication.
 *
 * @note	Sets legs, starts ADC, mailbox and threads.
 *
 * @note 	ADC1 CH13 is used.
 */
void indicationInit(void);

/*
 * @brief	Sets permission to get new values to the potentiometer.
 *
 * @param[in]	permission	New permission for the potentiometer.
 */
void setPotentPermission(bool permission);

/*
 * @brief	Gets the current value of the permission to get new values to the potentiometer.
 *
 * @param[out]		The current value of the permission for the potentiometer.
 */
bool getPotentPermission(void);

/*
 * @brief	Gets the current value of the operating mode.
 *
 * @param[out]		The current value of the operating mode.
 */
uint8_t getOperatingMode(void);

/*
 * @brief	Gets the current value of the string that we want to tune.
 *
 * @param[out]		The current value of the string that we want to tune.
 */
uint8_t getCurrentString(void);

/*
 * @brief	Sets new values to the string LEDs.
 *
 * @note 	Sends the msg to the mailbox that we have new values for LEDs.
 *
 * @param[in]	newValue	New values to the string LEDs
 */
void setStringLeds(uint8_t *newValue);

/*
 * @brief	Resets the string LEDs to inital values.
 */
void resetsLeds(void);

/*
 * @brief	Turns off all LEDs.
 */
void turnOffAllLeds(void);

/*
 * @brief	Checks the number of LEDs that are green depending on the operating mode.
 *
 * @param[out]		True - all LEDs depending on the operating mode are green.
 */
bool checkNeedToResetLeds(void);

#endif /* INCLUDE_INDICATION_INDICATION_H_ */
