#ifndef INCLUDE_MODES_SIX_STRING_MODE_H_
#define INCLUDE_MODES_SIX_STRING_MODE_H_

#include "common.h"

typedef struct{
    float upperLimit;
    float lowerLimit;
} sixStringLimitsParams;

void functionality_check(peaksAllParams *peaksParams, stringFreqsParams *stringParams);

#endif /* INCLUDE_MODES_SIX_STRING_MODE_H_ */
