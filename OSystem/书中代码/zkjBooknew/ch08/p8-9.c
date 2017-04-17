#include "ch08.h"
#define OUR_CLOCK CLOCK_REALTIME
timer_t mytimer;
void timer_intr(int signo, siginfo_t *extra, void *cruft) // 定时器到期信号句柄
{
   int noverflow;
   if (signo==SIGINT) /* 用户输入的CRTL/C信号，终止程序执行 */
      exit(1);  
   /* 查看是否有超时 */
   if (noverflow = timer_getoverrun(*(timer_t *)extra->si_value.sival_ptr))
      printf("timer has overflowerd--error\n");
   printf("timer expiration\n");
   return;
}
main(int argc, char **argv)
{
   int c;
   struct itimerspec i;
   struct timespec resolution;
   struct sigaction sa;
   sigset_t allsigs;
   struct sigevent timer_event;
   /* 首先保证存在所希望的时钟 */
   if (clock_getres(OUR_CLOCK, &resolution)<0)
      err_exit("clock_getres");
   printf("Clock resolution %d sec %d nsec\n", 
             resolution.tv_sec, resolution.tv_nsec);
   /* 设置定时器到期信号通知方式 */
   timer_event.sigev_notify=SIGEV_SIGNAL; /* 生成信号 */
   timer_event.sigev_signo=SIGRTMIN;       /* 要发送的信号 */
   timer_event.sigev_value.sival_ptr=(void *)&mytimer; /* 携带定时器ID指针 */
   /* 创建定时器 */
   if (timer_create(OUR_CLOCK, &timer_event, &mytimer)<0) 
      err_exit("timer_create");
   /* 捕获定时器到期信号 */
   sigemptyset(&sa.sa_mask);
   sigaddset(&sa.sa_mask,SIGRTMIN);  /* 句柄函数中屏蔽SIGRTMIN信号 */
   sa.sa_flags=SA_SIGINFO;             /* 实时信号 */
   sa.sa_sigaction=timer_intr;
   sigaction(SIGRTMIN, &sa, NULL);
   /* 捕获Ctr-c信号 */
   sigaction(SIGINT, &sa, NULL);
   /* 确定定时时间并设置定时器 */
   i.it_interval.tv_sec=0;
   i.it_interval.tv_nsec=resolution.tv_nsec*10; /* 定时间隔时间为分辨率的10倍*/
   i.it_value=i.it_interval;
   if (timer_settime(mytimer, 0, &i, NULL)<0)
      err_exit("timer_settime");
   sigemptyset(&allsigs);
   while(1){    /* 通过输入CRTL/C终止程序执行 */
         sigsuspend(&allsigs);    // 等待定时器到期信号
   }
}
