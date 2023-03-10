#include "six_string_mode.h"

static float freqsDecomposition[6][10];
static uint8_t numOfElemInColom[6] = {0};

static sixStringLimitsParams sixStringLimits[] = {
    {.lowerLimit = 50   , .upperLimit = 96.2 }, // 65
    {.lowerLimit = 96.3 , .upperLimit = 128.4},
    {.lowerLimit = 128.5, .upperLimit = 171.4},
    {.lowerLimit = 171.5, .upperLimit = 221.5},
    {.lowerLimit = 221.6, .upperLimit = 288.3},
    {.lowerLimit = 288.4, .upperLimit = 385  }
};

void init_params_six_string(stringFreqsParams *stringParams){
    stringParams->Error = false;
    for (uint8_t colom = 0; colom < 6; colom++){
        for (uint8_t row = 0; row < 10; row++){
            freqsDecomposition[colom][row] = 0;
        }
        numOfElemInColom[colom] = 0;
    }
}

void writes_zeros_to_six_string_array(stringFreqsParams *stringParams){
    for (uint8_t string = 0; string < 6; string++){
        stringParams->sixStringFreqs[string] = 0;
    }
}

void functionality_check(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    stringParams->Error = !((peaksParams->freqs[0] >= sixStringLimits[0].lowerLimit) &&
                            (peaksParams->freqs[0] <= sixStringLimits[5].upperLimit) &&
                            (peaksParams->lengthOfArrays > 1));
}

void freqs_decomposition_by_limits(peaksAllParams *peaksParams){
    for (uint8_t string = 0; string < 6; string++){
        for (uint8_t peak = 0; peak < peaksParams->lengthOfArrays; peak++){
            if ((peaksParams->freqs[peak] >= sixStringLimits[string].lowerLimit) &&
                (peaksParams->freqs[peak] <  sixStringLimits[string].upperLimit)){

                freqsDecomposition[string][numOfElemInColom[string]] = peaksParams->freqs[peak];
                numOfElemInColom[string] += 1;
            }
        }
    }
}

void multiplicity_check_six_string(peaksAllParams *peaksParams, stringFreqsParams *stringParams, float investigatedFreq){
    for (uint8_t i = 0; i < peaksParams->lengthOfArrays; i++){
        investigatedFreq = peaksParams->freqs[i] / investigatedFreq;
        if (investigatedFreq <= (round(investigatedFreq) + 0.05) &&
            investigatedFreq >= (round(investigatedFreq) - 0.05) &&
            (investigatedFreq > 1.1) && (investigatedFreq < 2.1)){

            stringParams->Error = false;
            break;
        }
        else {
           stringParams->Error = true;
        }
    }
}

void find_first_freq(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    bool flag = false;
    for (uint8_t string = 0; (string < 6) && !flag; string++){
        switch (numOfElemInColom[string]){
        case 0:
            stringParams->Error = true;
            break;
        case 1:
            multiplicity_check_six_string(peaksParams, stringParams, freqsDecomposition[string][0]);
            if (stringParams->Error == false){
                flag = true;
                stringParams->sixStringFreqs[string] =  freqsDecomposition[string][0];
            }
            break;
        default:
            stringParams->Error = true;
            flag = true;
            break;
        }
    }
    if (stringParams->Error == true) writes_zeros_to_six_string_array(stringParams);
}

void print_freqs_decomosition(void){
    for (uint8_t colom = 0; colom < 6; colom++){
        if (numOfElemInColom[colom] > 0){
            for (uint8_t row = 0; row < numOfElemInColom[colom]; row++){
                dbgPrintf("%0.1f   ", freqsDecomposition[colom][row]);
            }
        }
        else dbgPrintf("0.0     ");
        dbgPrintf("\r\n");
    }
}

void sixStringMode(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    init_params_six_string(stringParams);
    functionality_check(peaksParams, stringParams);
    if (stringParams->Error == false){
        freqs_decomposition_by_limits(peaksParams);
        print_freqs_decomosition();
        find_first_freq(peaksParams, stringParams);
    }
    else{
        writes_zeros_to_six_string_array(stringParams);
    }
}
