#include "ch13.h"
#include "err_exit.h"
struct alarmtag {
   time_t    the_time;              // SIGALRM信号接收时间
   int       got_alarm;             // SIGALRM信号接收标志
} alarmtime;
void *signal_thread(void *);     // 专门处理程序终止信号的线程
void *work_thread(void *);       // 工作线程
void alarm_handler(int signal)  // SIGALRM信号捕获函数
{
//   printf("catch ALARM ,%d\n",pthread_self());
   time (&alarmtime.the_time);        /* 取当前原始时间  */
   alarmtime.got_alarm = 1;            /* 设置信号到达标志 */
}

int main (int argc, char *argv[])
{
   pthread_t  sig_tid, work_tid;     
   int rv; 
   sigset_t sig_set;
   struct sigaction sa;
   /* 设置SIGALRM信号的动作 */
   sa.sa_handler = alarm_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART; 
   if (sigaction(SIGALRM, &sa, NULL) == -1)   
      err_exit("sigaction failed");             // 信号动作设置出错 
   /* 屏蔽所有信号，包括SIGALRM,SIGINT */
   pthread_sigmask(SIG_SETMASK, NULL, &sig_set);
   sigaddset(&sig_set, SIGINT);
   sigaddset(&sig_set, SIGUSR1); 
   rv = pthread_sigmask (SIG_BLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* 创建信号处理线程，它继承设置的信号屏蔽 */
   rv = pthread_create (&sig_tid, NULL, signal_thread, NULL);
   check_error(rv, "pthread_create");
   /* 更改信号屏蔽，放开SIGALRM信号 */
   sigemptyset(&sig_set);
   sigaddset (&sig_set, SIGALRM);
   rv = pthread_sigmask (SIG_UNBLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* 创建工作线程，它继承新设置的信号屏蔽 */
   rv = pthread_create (&work_tid, NULL, work_thread, NULL);
   check_error(rv, "pthread_create");
   /* 等待线程终止 */
   rv = pthread_join(work_tid, NULL);
   check_error(rv, "pthread_join");
   rv = pthread_kill(sig_tid, SIGUSR1);
   rv = pthread_join(sig_tid, NULL);
   check_error(rv, "pthread_join");
   printf("Good Bye\n");
   exit(0);
}

void *work_thread(void *arg)  /* 工作线程 */
{
   int i=0;
   alarmtime.got_alarm=0;
   printf("Work_thread: I am runing, my tid is: %lu\n",pthread_self());
   alarm(5);                         // 设置一秒的定时，这是发送给进程的信号
   printf("Work_thread: I set a alarm and go to sleep now.\n zzz~~~\n");
   while (!alarmtime.got_alarm);   // 运行直到被闹钟打断
//      for (i=0;i<10000000;i++)
//         for(j=0;j<100000;j++)
//           ;   // 每隔2000个迭代输出一段信息
//         printf(" ~~~zzz ");
//   }
   printf("Work_thread:The alam waken me up at %s", ctime(&alarmtime.the_time));
   printf("Work_thread:I finished.\n");
   pthread_exit(NULL);
}
void *signal_thread (void *arg)   /* 专门处理信号的线程 */
{
   int   sig, rv;
   sigset_t   wait_set, sig_set;   
   printf("Signal_thread:I am running, my tid is %lu\n", pthread_self());    
   /* 等待指定的信号 */
   sigemptyset(&wait_set);
   sigaddset (&wait_set, SIGUSR1);  
   sigaddset (&wait_set, SIGINT);  
   rv = sigwait (&wait_set, &sig);
   check_error(rv, "sigwait");
   switch (sig) {
   case SIGINT:     /* 处理 SIGTERM  */
      // ...  结束之前的清场处理代码
      /* 放开信号屏蔽，并以默认动作再次生成该信号使自己终止，从而导致进程终止. */
      printf ("Signal_thread:I received SIGINT:%d\n", sig);
      sigemptyset(&sig_set);
      sigaddset (&sig_set, sig); 
      rv = pthread_sigmask(SIG_UNBLOCK, &sig_set, NULL);
      signal(sig, SIG_DFL);   // 程序7-3
      raise (sig);              // 发送给自己的同步信号
      pthread_exit(NULL);      // 应当不会执行
   case SIGUSR1:
      printf ("Signal_thread:I received SIGUSR1 and finished.\n");
      pthread_exit(NULL); 
   default:         /* 其它信号，不应当出现 */
      fprintf (stderr, "Unexpected signal %d ", sig);
      exit(0); 
   }
}
