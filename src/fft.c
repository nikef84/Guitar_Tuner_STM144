#include "fft.h"
#include "terminal_write.h"

/*
 * @brief   Real and imaginary parts of the signal.
 *
 * @note    Initial value of data_re is the signal.
 *          Initial value of data_im is {0}.
 */
static float data_re[SIGNAL_LENGTH] = {0};
static float data_im[SIGNAL_LENGTH] = {0};

/*
 * @brief   Reverses bits by index.
 *
 *
 * @Example     0 (0b000) --> 0 (0b000)
 *              1 (0b001) --> 4 (0b100)
 *              2 (0b010) --> 2 (0b010)
 *              3 (0b011) --> 6 (0b110)
 *              4 (0b100) --> 1 (0b001)
 *              5 (0b101) --> 5 (0b101)
 *              6 (0b110) --> 3 (0b011)
 *              7 (0b111) --> 7 (0b111)
 *
 * @param[in]   data_re     Real part of the signal.
 *              data_im     Imaginary part of the signal.
 * @notapi
 */
void rearrange(float *data_re, float *data_im){
  uint16_t target = 0;
    for(uint16_t position=0; position<SIGNAL_LENGTH; position++){
        if(target>position){
            const float temp_re = data_re[target];
            const float temp_im = data_im[target];
            data_re[target] = data_re[position];
            data_im[target] = data_im[position];
            data_re[position] = temp_re;
            data_im[position] = temp_im;
      }
      uint16_t mask = SIGNAL_LENGTH;
      while(target & (mask >>=1)) target &= ~mask;

      target |= mask;
    }
}

/*
 * @brief   Does all the calculations of the FFT algorithm.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error here.
 *
 * @note    I don't know how it works...
 *
 * @param[in]   data_re     Real part of the signal.
 *              data_im     Imaginary part of the signal.
 *
 * @notapi
 */
void compute(float *data_re, float *data_im){
    const float pi = -3.14159265358979323846;
    for(uint16_t step=1; step<SIGNAL_LENGTH; step <<=1){
        const uint16_t jump = step << 1;
        const float step_d = (float) step;
        float twiddle_re = 1.0;
        float twiddle_im = 0.0;
        for(uint16_t group=0; group<step; group++){
            for(uint16_t pair=group; pair<SIGNAL_LENGTH; pair+=jump){
                const uint16_t match = pair + step;
                const float product_re = twiddle_re*data_re[match]-twiddle_im*data_im[match];
                const float product_im = twiddle_im*data_re[match]+twiddle_re*data_im[match];
                data_re[match] = data_re[pair]-product_re;
                data_im[match] = data_im[pair]-product_im;
                data_re[pair] += product_re;
                data_im[pair] += product_im;
            }

            // we need the factors below for the next iteration
            // if we don't iterate then don't compute
            if(group+1 == step) continue;

            float angle = pi*((float) group+1)/step_d;
            twiddle_re = cos(angle);
            twiddle_im = sin(angle);
        }
    }
}

/*
 * @brief   Inits real and imaginary part of signal.
 *
 * @note    Initial value of data_re is the signal.
 *          Initial value of data_im is {0}.
 *
 * @param[in]   signal     Array of real numbers with which we will calculate the FFT.
 *
 * @notapi
 */
void dataInit(uint16_t *signal){
    for (uint16_t i = 0; i < SIGNAL_LENGTH; i++){
        data_re[i] = signal[i];
        data_im[i] = 0;
    }
}

/*
 * @brief   Calculates the absolute value of complex numbers.
 *
 * @param[in]   spec        Result of FFT.
 *              data_re     Real part of the signal.
 *              data_im     Imaginary part of the signal.
 * @notapi
 */
void dataAbs(float *spec, float *data_re, float *data_im){
    for (uint16_t i = 0; i < (SIGNAL_LENGTH / 2); i++){
        spec[i] = sqrt(pow(data_re[i], 2) + pow(data_im[i], 2));
    }
}

/*
 * @brief   Transforms the result somehow.
 *
 * @note    I don't know why we need it. This transformation is in LabVeiw.
 *
 * @param[in]   spec        Result of FFT.
 *
 * @notapi
 */
void likeInLabView(float *spec){
    float first_num = spec[0] / SIGNAL_LENGTH;
    for (uint16_t i = 0; i < (SIGNAL_LENGTH / 2); i++){
        spec[i] = (spec[i] / SIGNAL_LENGTH) * sqrt(2);
    }
    spec[0] = first_num;
}

/*
 * @brief   Makes the FFT of the signal and returns the spec of this signal.
 *
 * @note    It works like in Labview.
 *
 * @note    SIGNAL_LENGTH MUST be 2^n!!! Or it will lead to error here.
 *
 * @param[in]   spec        Result of FFT.
 *              signal      Array of real numbers with which we will calculate the FFT.
 */
void fft(float *spec, uint16_t *signal){
    dataInit(signal);
    rearrange(data_re, data_im);
    compute(data_re, data_im);
    dataAbs(spec, data_re, data_im);
    likeInLabView(spec);
}
