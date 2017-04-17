#include "ch08.h"
#define DEFAULT_NSECS 100000
struct timeval t1, t2;
void alrm_handler (int signal)  /* 定时器到期信号句柄,输出实际间隔时间 */
{
   gettimeofday(&t2, NULL);
   printf ("time interval %ld:\n", t2.tv_sec*1000000+t2.tv_usec
              -(t1.tv_sec*1000000+t1.tv_usec));
   t1=t2;
}
main(int argc, char **argv)
{
   int time;
   struct itimerval i;
   struct sigaction sa;
   sigset_t allsigs;
   i.it_interval.tv_sec=0;
   i.it_interval.tv_usec=DEFAULT_NSECS;
   switch (argc) {   /* 处理参数*/
   case 1:
      break;
   case 2:
      i.it_interval.tv_usec=atoi(argv[1]);
      i.it_interval.tv_sec=0;
      while (i.it_interval.tv_usec>1000000) {
         i.it_interval.tv_usec-=1000000;
         i.it_interval.tv_sec++;
      }
      printf("Time interval: %d sec %d usec\n",
                i.it_interval.tv_sec, i.it_interval.tv_usec);
      break;
   default:
      fprintf(stderr, "Usage: %s {usecs}\n", argv[0]);
      exit(2);
   }
   i.it_value=i.it_interval;
   /* 设置信号句柄 */
   sigemptyset(&sa.sa_mask);
   sigaddset(&sa.sa_mask,SIGALRM);
   sa.sa_flags=0;
   sa.sa_handler=alrm_handler;
   if (sigaction(SIGALRM, &sa, NULL)<0)  
      err_exit("sigaction");
   gettimeofday(&t1, NULL);     /* 记录定时开始时间*/
   if (setitimer(ITIMER_REAL, &i, NULL)<0)
      err_exit("setitimer");
   sigemptyset(&allsigs);
   while (1){
      sigsuspend(&allsigs);
   }
   exit(1);
}
