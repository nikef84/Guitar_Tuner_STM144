#include "common.h"
#include "tests.h"
#include "terminal_write.h"

// Будем использовать первый и третий таймеры
GPTDriver *timer1 = &GPTD1;
systime_t time1, time2;
uint16_t count = 0;

// Определяем две функции обработчика прерываний

// Первая функция просто моргает лампочкой
void cbgptfun1(GPTDriver *gptp)
{
    (void)gptp;
    count += 1;
    if (count == 500){
    	palToggleLine(LINE_LED1);
		time2 = chVTGetSystemTime() - time1;
		time1 = chVTGetSystemTime();
		count = 0;
    }

}


// Настраиваем частоту первого таймера 50_000Гц (предделитель 4320, целое число, меньше чем 2^16) и указывает первую функцию как обработчик прерываний
GPTConfig gpt1_conf = {
    .frequency = 50000,
    .callback = cbgptfun1,
    .cr2 = 0,
    .dier = 0
};
void gpt_test(void) {

    halInit();
    chSysInit();
    debugStreamInit();
    // Включим оба таймера
    gptStart(timer1, &gpt1_conf);
    // Первый запустим в непрерывном режиме с частотой 2Гц
    gptStartContinuous(timer1, 50);
    time1 = chVTGetSystemTime();
    while (true) {
        dbgPrintf("%d\r\n", time2);
        // Наблюдаем, как две лампочки синхронно моргают
        chThdSleepMilliseconds(1000);
    }
}
