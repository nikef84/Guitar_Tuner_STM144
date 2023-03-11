#include "six_string_mode.h"

static float freqsDecomposition[6][10];
static uint8_t numOfElemInColom[6] = {0};
static uint8_t numOfFirstZeroElem = 0;

static sixStringLimitsParams sixStringLimits[] = {
    {.lowerLimit = 65   , .upperLimit = 96.2 },
    {.lowerLimit = 96.3 , .upperLimit = 128.4},
    {.lowerLimit = 128.5, .upperLimit = 171.4},
    {.lowerLimit = 171.5, .upperLimit = 221.5},
    {.lowerLimit = 221.6, .upperLimit = 288.3},
    {.lowerLimit = 288.4, .upperLimit = 385  }
};

static uint8_t tempLimitsLength = 0;

static sixStringLimitsParams tempLimits[] = {
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0},
    {.lowerLimit = 0, .upperLimit = 0}
};

void init_params_six_string(stringFreqsParams *stringParams){
    stringParams->Error = false;
    numOfFirstZeroElem = 0;
    tempLimitsLength = 0;
    tempLimitsLength = 0;
    for (uint8_t string = 0; string < 6; string++){
        for (uint8_t row = 0; row < 10; row++){
            freqsDecomposition[string][row] = 0;
        }
        numOfElemInColom[string] = 0;
        tempLimits[string].lowerLimit = 0;
        tempLimits[string].upperLimit = 0;
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
    investigatedFreq = investigatedFreq * 2;
    for (uint8_t peak = 0; peak < peaksParams->lengthOfArrays; peak++){
        if ((peaksParams->freqs[peak] <= investigatedFreq + 5) &&
            (peaksParams->freqs[peak] >= investigatedFreq - 5)){

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
                stringParams->sixStringFreqs[string] =  freqsDecomposition[string][0];
                numOfFirstZeroElem = string;
            }
            flag = true;
            break;
        default:
            stringParams->Error = true;
            flag = true;
            break;
        }
    }
}

bool check_if_freqs_were_lost(float investigatedFreq){
    bool freqsWereLost = false;
    for (uint8_t i = 0; (i < tempLimitsLength) && !freqsWereLost; i++){
        for (uint8_t multiplier = 1; multiplier <= 5; multiplier++){
            if ((investigatedFreq <= tempLimits[i].upperLimit * multiplier) &&
               (investigatedFreq >= tempLimits[i].upperLimit * multiplier)){

                freqsWereLost = true;
                break;
            }
        }
    }
    return freqsWereLost;
}


void find_all_freqs_exept_first(peaksAllParams *peaksParams, stringFreqsParams *stringParams){
    bool flag = false;
    float potentialFreq, investigatedFreqAbs;
    uint8_t numOfPotentialFreq ;
    for (uint8_t string = 1; (string < 6 - numOfFirstZeroElem) && !flag; string++){
        potentialFreq = 0;
        numOfPotentialFreq = 0;
        for (uint8_t i = 0; i < numOfElemInColom[numOfFirstZeroElem + string]; i++){
            // ok
            numOfPotentialFreq += 1;
            if (check_if_freqs_were_lost(freqsDecomposition[numOfFirstZeroElem + string][i]) == false){
                for (uint8_t j = 0; j < numOfFirstZeroElem + string; j++){
                    if (stringParams->sixStringFreqs[j] != 0){
                        investigatedFreqAbs = freqsDecomposition[numOfFirstZeroElem + string][i] / stringParams->sixStringFreqs[j];
                        if ((investigatedFreqAbs <= round(investigatedFreqAbs) + 0.05) &&
                            (investigatedFreqAbs >= round(investigatedFreqAbs) - 0.05)){
                            numOfPotentialFreq -= 1;

                            break;
                        }
                        potentialFreq = freqsDecomposition[numOfFirstZeroElem + string][i];
                    }
                }
            }
        }
        switch (numOfPotentialFreq){
        case 0:
            tempLimits[tempLimitsLength] = sixStringLimits[numOfFirstZeroElem + string];
            tempLimitsLength += 1;
            break;
        case 1:
            multiplicity_check_six_string(peaksParams, stringParams, potentialFreq);
            if (stringParams->Error == false){
                stringParams->sixStringFreqs[numOfFirstZeroElem + string] = potentialFreq;
                dbgPrintf("q\r\n");
            }
            else {
                writes_zeros_to_six_string_array(stringParams);
                flag = true;
            }
            break;
        default:
            stringParams->Error = true;
            writes_zeros_to_six_string_array(stringParams);
            flag = true;
            break;
        }
    }
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
//        print_freqs_decomosition();
        find_first_freq(peaksParams, stringParams);
        if (stringParams->Error == false){
            find_all_freqs_exept_first(peaksParams, stringParams);
        }
        else writes_zeros_to_six_string_array(stringParams);
    }
    else{
        writes_zeros_to_six_string_array(stringParams);
    }
}
