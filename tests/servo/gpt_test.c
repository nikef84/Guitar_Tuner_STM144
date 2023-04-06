#include "common.h"
#include "tests.h"
#include "terminal_write.h"

// ����� ������������ ������ � ������ �������
GPTDriver *timer1 = &GPTD1;
systime_t time1, time2;
uint16_t count = 0;

// ���������� ��� ������� ����������� ����������

// ������ ������� ������ ������� ���������
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


// ����������� ������� ������� ������� 50_000�� (������������ 4320, ����� �����, ������ ��� 2^16) � ��������� ������ ������� ��� ���������� ����������
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
    // ������� ��� �������
    gptStart(timer1, &gpt1_conf);
    // ������ �������� � ����������� ������ � �������� 2��
    gptStartContinuous(timer1, 50);
    time1 = chVTGetSystemTime();
    while (true) {
        dbgPrintf("%d\r\n", time2);
        // ���������, ��� ��� �������� ��������� �������
        chThdSleepMilliseconds(1000);
    }
}
