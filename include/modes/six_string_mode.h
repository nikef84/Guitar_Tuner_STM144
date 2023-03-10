#ifndef INCLUDE_MODES_SIX_STRING_MODE_H_
#define INCLUDE_MODES_SIX_STRING_MODE_H_

#include "common.h"
#include "terminal_write.h"

typedef struct{
    float upperLimit;
    float lowerLimit;
} sixStringLimitsParams;

void sixStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams);

#endif /* INCLUDE_MODES_SIX_STRING_MODE_H_ */
