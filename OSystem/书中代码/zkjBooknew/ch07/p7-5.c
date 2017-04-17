#include "ch07.h"
volatile sig_atomic_t flag = 0;   /* 该标志在 SIGALRM 信号句柄中被设置. */
int main (void)
{
    sigset_t block_alarm;
    /* 初始信号集合 */
    sigemptyset (&block_alarm);
    sigaddset (&block_alarm, SIGPROF);   /* 要阻塞的信号是SIGALRM */
     ...
    while (1){
        sigprocmask (SIG_BLOCK, &block_alarm, NULL);    /* 设置信号屏蔽 */
        if (flag){   /* 检查信号到达否,若到达则清除标志flag  */         
            ACTIONS-IF-ARRIVED
            flag = 0;
        }
        sigprocmask (SIG_UNBLOCK, &block_alarm, NULL);  /* 解除信号屏蔽 */   
        ...
    }
}

