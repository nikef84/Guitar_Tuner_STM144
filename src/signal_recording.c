#include "signal_recording.h"

// @brief   An array for recording a waiting signal before the main signal.
static uint16_t waitSignaBuf[WAIT_SIGNAL_NUMBER_OF_SAMLES] = {0};
static msg_t flag;

/*
 * @brief       Waits a high amlitude from the recording signal.
 *
 * @note        It can get stuck in the loop if you choose wrong limits.
 *
 * @param[in]   buf                 An array in which data will be write from the adc.
 *              numberOfSamples    Number of the adc conversion which will be write to the array.
 *                                  This number is equal to lenght of input array (buf).
 *
 * @notapi
 */
void waitingForMainSignal(uint16_t *buf, uint16_t numberOfSamples){
    flag = MSG_TIMEOUT; // Shows if it catch a high amplitude.

    while (flag == MSG_TIMEOUT){
        adcSimpleRead(buf, numberOfSamples); // Record the short signal.

        // Cheak the recorded signal for a high amplitude.
        for (uint8_t i = 0; i < numberOfSamples; i++){
            if (buf[i] > WAIT_SIGNAL_UPPER_LIMIT || buf[i] < WAIT_SIGNAL_LOWER_LIMIT) flag = MSG_OK;
        }
    }
}

/*
 * @brief   Record main signal after detecting a high amplitude.
 *
 * @param[in]   mainSignalBuf           An array in which data will be write from the adc.
 *              MAIN_SIGNAL_LENGTH      Number of the adc conversion which will be write to the array.
 *                                      This number is equal to lenght of input array (buf).
 */
void recordMainSignal(uint16_t *waitSignalBuf){
    waitingForMainSignal(waitSignaBuf, WAIT_SIGNAL_NUMBER_OF_SAMLES); // Waits a high amlitude.

    adcSimpleRead(waitSignalBuf, MAIN_SIGNAL_LENGTH); // Records the main signal.
}
