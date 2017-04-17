#include "ch14.h"
#define OUTPUTSCHEDPARAM(policy, priority)   printf(         \
                     "Thread %lx: Policy=%s, priority=%d\n", \
                     pthread_self(),                       \
                     (policy==SCHED_FIFO?"FIFO"            \
                       :(policy==SCHED_RR?"RR"             \
                       :(policy==SCHED_OTHER?"OTHER"       \
                       :"unknown"))), priority)
#include "p13-13.c"
#include "p14-6.c"

barrier_t barrier;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
 
void *t_routine(void *n)
{
   int rv, mypolicy, thread_no = (int)n;
   struct sched_param myparam;
   barrier_wait(&barrier);             // 栅栏等齐所有线程到达，程序13-13
   rv = pthread_mutex_lock(&mutex);   // 开始竞争互斥变量 
   check_error(rv, "mutex_lock");
   printf("Thread %d :",thread_no);
   /* 打印出线程的调度策略和优先级 */
   rv = pthread_getschedparam(pthread_self(),
                                   &mypolicy, &myparam);
   check_error(rv, "getschedparam");
   OUTPUTSCHEDPARAM(mypolicy, myparam.sched_priority);
   rv = pthread_mutex_unlock(&mutex);  // 释放互斥变量
   check_error(rv, "mutex_unlock");
}

int main(void)
{
   int rv, priority,  policy;
   struct sched_param param;
   struct sched_thread t_param;

   /* 初始化一个5线程同步的栅栏 */
   rv = barrier_init(&barrier, 5);    // 程序13-13 
   check_error(rv, "barrier_init");

   /* 输出初始线程的调度策略和优先级 */
   rv = pthread_getschedparam(pthread_self(), &policy, &param);
   check_error(rv,"main: getschedparam");
   OUTPUTSCHEDPARAM(policy, param.sched_priority);

   /*  创建4个不同调度策略和优先级的线程  */
   t_param.thread_func = t_routine;
   t_param.policy = SCHED_FIFO;
   t_param.num = 1;
   t_param.priority = sched_get_priority_min(SCHED_FIFO); 
   create_exlicit_sched_threads(&t_param); 

   t_param.num = 2;
   t_param.priority +=2;
   create_exlicit_sched_threads(&t_param);

   t_param.policy = SCHED_RR;
   t_param.num=3;
   t_param.priority = sched_get_priority_min(SCHED_RR);
   create_exlicit_sched_threads(&t_param);

   t_param.num=4;
   t_param.priority = sched_get_priority_max(SCHED_RR);
   create_exlicit_sched_threads(&t_param);

  /* 改变自身的调度策略和优先级 */
   if (policy == SCHED_RR) {  // 调度策略是我们需要的策略，只提升优先级
      rv = pthread_setschedprio(pthread_self(),t_param.priority+6);
      check_error(rv, "getschedparam");
   } else {                       // 否则改变策略和优先级 
      param.sched_priority += 10;
      rv = pthread_setschedparam(pthread_self(),SCHED_RR, &param);
      check_error(rv, "getschedparam");
   }
   t_routine(0);     // 参与线程竞争
   pthread_exit((void *)NULL);
}

