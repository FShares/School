#include "ch08.h"
#define OUR_CLOCK CLOCK_REALTIME
timer_t mytimer;
void timer_intr(int signo, siginfo_t *extra, void *cruft) // ��ʱ�������źž��
{
   int noverflow;
   if (signo==SIGINT) /* �û������CRTL/C�źţ���ֹ����ִ�� */
      exit(1);  
   /* �鿴�Ƿ��г�ʱ */
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
   /* ���ȱ�֤������ϣ����ʱ�� */
   if (clock_getres(OUR_CLOCK, &resolution)<0)
      err_exit("clock_getres");
   printf("Clock resolution %d sec %d nsec\n", 
             resolution.tv_sec, resolution.tv_nsec);
   /* ���ö�ʱ�������ź�֪ͨ��ʽ */
   timer_event.sigev_notify=SIGEV_SIGNAL; /* �����ź� */
   timer_event.sigev_signo=SIGRTMIN;       /* Ҫ���͵��ź� */
   timer_event.sigev_value.sival_ptr=(void *)&mytimer; /* Я����ʱ��IDָ�� */
   /* ������ʱ�� */
   if (timer_create(OUR_CLOCK, &timer_event, &mytimer)<0) 
      err_exit("timer_create");
   /* ����ʱ�������ź� */
   sigemptyset(&sa.sa_mask);
   sigaddset(&sa.sa_mask,SIGRTMIN);  /* �������������SIGRTMIN�ź� */
   sa.sa_flags=SA_SIGINFO;             /* ʵʱ�ź� */
   sa.sa_sigaction=timer_intr;
   sigaction(SIGRTMIN, &sa, NULL);
   /* ����Ctr-c�ź� */
   sigaction(SIGINT, &sa, NULL);
   /* ȷ����ʱʱ�䲢���ö�ʱ�� */
   i.it_interval.tv_sec=0;
   i.it_interval.tv_nsec=resolution.tv_nsec*10; /* ��ʱ���ʱ��Ϊ�ֱ��ʵ�10��*/
   i.it_value=i.it_interval;
   if (timer_settime(mytimer, 0, &i, NULL)<0)
      err_exit("timer_settime");
   sigemptyset(&allsigs);
   while(1){    /* ͨ������CRTL/C��ֹ����ִ�� */
         sigsuspend(&allsigs);    // �ȴ���ʱ�������ź�
   }
}
