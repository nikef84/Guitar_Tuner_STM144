#ifndef INCLUDE_INDICATION_INDICATION_H_
#define INCLUDE_INDICATION_INDICATION_H_

#include "common.h"
#include "adc_lld.h"
#include "terminal_write.h"

#define POTENT_MODE_ADC_STEP			586
#define POTENT_MODE_ADC_MIN				0
#define POTENT_MODE_ADC_MAX				4096

#define POTENT_NUM_OF_MODES				7

void indicationInit(void);

#endif /* INCLUDE_INDICATION_INDICATION_H_ */
