#include "ch13.h"
#include "err_exit.h"
struct alarmtag {
   time_t    the_time;              // SIGALRM�źŽ���ʱ��
   int       got_alarm;             // SIGALRM�źŽ��ձ�־
} alarmtime;
void *signal_thread(void *);     // ר�Ŵ��������ֹ�źŵ��߳�
void *work_thread(void *);       // �����߳�
void alarm_handler(int signal)  // SIGALRM�źŲ�����
{
//   printf("catch ALARM ,%d\n",pthread_self());
   time (&alarmtime.the_time);        /* ȡ��ǰԭʼʱ��  */
   alarmtime.got_alarm = 1;            /* �����źŵ����־ */
}

int main (int argc, char *argv[])
{
   pthread_t  sig_tid, work_tid;     
   int rv; 
   sigset_t sig_set;
   struct sigaction sa;
   /* ����SIGALRM�źŵĶ��� */
   sa.sa_handler = alarm_handler;
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_RESTART; 
   if (sigaction(SIGALRM, &sa, NULL) == -1)   
      err_exit("sigaction failed");             // �źŶ������ó��� 
   /* ���������źţ�����SIGALRM,SIGINT */
   pthread_sigmask(SIG_SETMASK, NULL, &sig_set);
   sigaddset(&sig_set, SIGINT);
   sigaddset(&sig_set, SIGUSR1); 
   rv = pthread_sigmask (SIG_BLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* �����źŴ����̣߳����̳����õ��ź����� */
   rv = pthread_create (&sig_tid, NULL, signal_thread, NULL);
   check_error(rv, "pthread_create");
   /* �����ź����Σ��ſ�SIGALRM�ź� */
   sigemptyset(&sig_set);
   sigaddset (&sig_set, SIGALRM);
   rv = pthread_sigmask (SIG_UNBLOCK, &sig_set, NULL);
   check_error(rv, "pthread_sigmask");
   /* ���������̣߳����̳������õ��ź����� */
   rv = pthread_create (&work_tid, NULL, work_thread, NULL);
   check_error(rv, "pthread_create");
   /* �ȴ��߳���ֹ */
   rv = pthread_join(work_tid, NULL);
   check_error(rv, "pthread_join");
   rv = pthread_kill(sig_tid, SIGUSR1);
   rv = pthread_join(sig_tid, NULL);
   check_error(rv, "pthread_join");
   printf("Good Bye\n");
   exit(0);
}

void *work_thread(void *arg)  /* �����߳� */
{
   int i=0;
   alarmtime.got_alarm=0;
   printf("Work_thread: I am runing, my tid is: %lu\n",pthread_self());
   alarm(5);                         // ����һ��Ķ�ʱ�����Ƿ��͸����̵��ź�
   printf("Work_thread: I set a alarm and go to sleep now.\n zzz~~~\n");
   while (!alarmtime.got_alarm);   // ����ֱ�������Ӵ��
//      for (i=0;i<10000000;i++)
//         for(j=0;j<100000;j++)
//           ;   // ÿ��2000���������һ����Ϣ
//         printf(" ~~~zzz ");
//   }
   printf("Work_thread:The alam waken me up at %s", ctime(&alarmtime.the_time));
   printf("Work_thread:I finished.\n");
   pthread_exit(NULL);
}
void *signal_thread (void *arg)   /* ר�Ŵ����źŵ��߳� */
{
   int   sig, rv;
   sigset_t   wait_set, sig_set;   
   printf("Signal_thread:I am running, my tid is %lu\n", pthread_self());    
   /* �ȴ�ָ�����ź� */
   sigemptyset(&wait_set);
   sigaddset (&wait_set, SIGUSR1);  
   sigaddset (&wait_set, SIGINT);  
   rv = sigwait (&wait_set, &sig);
   check_error(rv, "sigwait");
   switch (sig) {
   case SIGINT:     /* ���� SIGTERM  */
      // ...  ����֮ǰ���峡�������
      /* �ſ��ź����Σ�����Ĭ�϶����ٴ����ɸ��ź�ʹ�Լ���ֹ���Ӷ����½�����ֹ. */
      printf ("Signal_thread:I received SIGINT:%d\n", sig);
      sigemptyset(&sig_set);
      sigaddset (&sig_set, sig); 
      rv = pthread_sigmask(SIG_UNBLOCK, &sig_set, NULL);
      signal(sig, SIG_DFL);   // ����7-3
      raise (sig);              // ���͸��Լ���ͬ���ź�
      pthread_exit(NULL);      // Ӧ������ִ��
   case SIGUSR1:
      printf ("Signal_thread:I received SIGUSR1 and finished.\n");
      pthread_exit(NULL); 
   default:         /* �����źţ���Ӧ������ */
      fprintf (stderr, "Unexpected signal %d ", sig);
      exit(0); 
   }
}
