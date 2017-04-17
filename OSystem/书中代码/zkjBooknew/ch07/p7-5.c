#include "ch07.h"
volatile sig_atomic_t flag = 0;   /* �ñ�־�� SIGALRM �źž���б�����. */
int main (void)
{
    sigset_t block_alarm;
    /* ��ʼ�źż��� */
    sigemptyset (&block_alarm);
    sigaddset (&block_alarm, SIGPROF);   /* Ҫ�������ź���SIGALRM */
     ...
    while (1){
        sigprocmask (SIG_BLOCK, &block_alarm, NULL);    /* �����ź����� */
        if (flag){   /* ����źŵ����,�������������־flag  */         
            ACTIONS-IF-ARRIVED
            flag = 0;
        }
        sigprocmask (SIG_UNBLOCK, &block_alarm, NULL);  /* ����ź����� */   
        ...
    }
}

