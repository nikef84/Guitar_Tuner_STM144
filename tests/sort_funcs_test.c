#include "common.h"
#include "terminal_write.h"
#include <stdlib.h>

static uint16_t index[21] = {20, 150, 900, 100, 50, 800, 600, 700, 550, 500, 850, 750, 450, 10, 40, 650, 950, 1000, 999, 1, 0};
static float amp[21] =      {10, 1.1, 2.2, 3.3, 15, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 1.2, 2.3, 20, 25, 2.4, 2.5, 2.55, 2.6, 1, 0};

//int cmp(const void *a, const void *b) {
//    return *(uint16_t*)a - *(uint16_t*)b;
//}
//
//void first_sort(void){
//    uint16_t add_index[20];
//    float add_amp[20];
//    for (uint16_t i = 0; i < 20; i++) {
//        add_index[i] = index[i];
//        add_amp[i] = amp[i];
//    }
//    qsort(index, 20, sizeof(uint16_t), cmp );
//    for (uint16_t i = 0; i < 20; i++){
//        for (uint16_t j = 0; j < 20; j++){
//            if (index[i] == add_index[j]) amp[i] = add_amp[j];
//        }
//    }
//
//}

void second_sort(uint8_t first, uint8_t last){
    if (first < last){
        uint8_t left = first;
        uint8_t right = last;
        uint16_t middle = index[(left + right) / 2];
        do{
            while (index[left] < middle) left++;
            while (index[right] > middle) right--;
            if (left <= right){
                uint16_t tmp_index = index[left];
                index[left] = index[right];
                index[right] = tmp_index;

                float tmp_amp = amp[left];
                amp[left] = amp[right];
                amp[right] = tmp_amp;

                left++;
                right--;
            }
        } while (left < right);
        second_sort(first, right);
        second_sort(left, last);
    }
}

void sortFuncsTest(void){
  halInit();
  chSysInit();
  debugStreamInit();
  dbgPrintf("start\r\n");
  systime_t begin = chVTGetSystemTime();
  second_sort(0, 19);
  systime_t end = chVTGetSystemTime();
  dbgPrintf("time = %d\r\n", end - begin);
  while (true) {
      for (uint8_t i = 0; i < 21; i++) dbgPrintf("%d   %0.2f\r\n", index[i], amp[i]);
      chThdSleepMilliseconds(100000);
  }
}
