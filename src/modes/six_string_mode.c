#include "six_string_mode.h"

static float freqsDecopmposition[6][10]
static sixStringLimitsParams sixStringLimits[] = {
    {.lowerLimit = 65   , .upperLimit = 96.2 },
    {.lowerLimit = 96.3 , .upperLimit = 128.4},
    {.lowerLimit = 128.5, .upperLimit = 171.4},
    {.lowerLimit = 171.5, .upperLimit = 221.5},
    {.lowerLimit = 221.6, .upperLimit = 288.3},
    {.lowerLimit = 288.4, .upperLimit = 385  }
};

void functionality_check(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    stringParams->Error = !((peaksParams->freqs[0] >= sixStringLimits[0].lowerLimit) &&
                            (peaksParams->freqs[0] <= sixStringLimits[5].upperLimit) &&
                            (peaksParams->lengthOfArrays > 1));
}
