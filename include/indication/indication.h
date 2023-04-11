#ifndef INCLUDE_INDICATION_INDICATION_H_
#define INCLUDE_INDICATION_INDICATION_H_

#include "common.h"
#include "adc_lld.h"
#include "terminal_write.h"

#define POTENT_MODE_ADC_STEP			586
#define POTENT_MODE_ADC_MIN				0
#define POTENT_MODE_ADC_MAX				4096

#define POTENT_NUM_OF_MODES				7

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

#define DIODE_NOT_ACTIVE				0
#define DIODE_GREEN_LIGHT				1
#define DIODE_RED_LIGHT					2

#define DIODE_STRING_1					0
#define DIODE_STRING_2					1
#define DIODE_STRING_3					2
#define DIODE_STRING_4					3
#define DIODE_STRING_5					4
#define DIODE_STRING_6					5
#define DIODE_SIX_STRING_MODE			6
#define DIODE_ONE_STRING_MODE			7
#define DIODE_NEW_STRING_VALUE			10
#define DIODE_RESET						25


void indicationInit(void);

void setPotentPermission(bool permission);
bool getPotentPermission(void);
void setDiodStrings(uint8_t *newValue);
uint8_t getOperatingMode(void);
uint8_t getCurrentString(void);
void resetsDiods(void);
bool checkNeedToResetDiodes(void);

#endif /* INCLUDE_INDICATION_INDICATION_H_ */
