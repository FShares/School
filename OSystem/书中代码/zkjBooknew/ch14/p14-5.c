#include "ch14.h"
typedef struct Sema{  
    pthread_mutex_t lock;
    pthread_cond_t cond;
    int count; 
} sema_t;    //信号量数据结构
sema_t semaphore = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 1};
#define THREADS 4

void cleanup_mutex(void *arg)  //互斥变量解锁/清理函数
{
    printf("\tthread %lx: cleanup/unlock_mutex\n", pthread_self());
    pthread_mutex_unlock((pthread_mutex_t *)arg);
}

void AquireSemaphore(sema_t *ps)
{
    pthread_mutex_lock(&ps->lock);
    pthread_cleanup_push(cleanup_mutex, &ps->lock); //建立互斥变量清理器
    while (ps->count == 0)
        pthread_cond_wait(&(ps->cond), &(ps->lock));
    --ps->count; 
    pthread_cleanup_pop(1);   // 释放互斥变量
}

void ReleaseSemaphore(sema_t *ps)
{
   pthread_mutex_lock(&ps->lock);
   ++ps->count;
   pthread_cond_signal(&ps->cond);
   pthread_mutex_unlock(&ps->lock);
}

void cleanup_sema(void *arg)   // 信号量清理器
{
   printf("\tthread %lx: cleanup_sema\n",pthread_self());
   ReleaseSemaphore((sema_t *)arg);
}

void * thread_routine(void * arg)  // 线程开始函数
{
   int rv;
   AquireSemaphore(&semaphore);    // 获得信号量
   pthread_cleanup_push(cleanup_sema, &semaphore);   // 建立信号量清理器
   printf ("   thread %lx: sleep\n", pthread_self());
   sleep(1);
   printf ("   thread %lx: waken from sleep\n", pthread_self());
   pthread_cleanup_pop(0);        // 弹出信号量清理器 
   ReleaseSemaphore(&semaphore);  // 释放信号量
}

int main(int argc, char* argv[])
{
   pthread_t thread_id[THREADS];
   int i, rv, *status;

   for (i=0; i<THREADS; i++) {  // 创建若干个线程
      rv = pthread_create (&thread_id[i], NULL, thread_routine, NULL);
      check_error(rv, "Create thread");
   }
   sleep (2);
   for (i=0; i<THREADS; i++) { // 睡眠2秒后再取消它们
      if ((rv = pthread_cancel (thread_id[i]))== ESRCH) // 线程可能已经终止
         printf("thread %lx dose not exist\n", thread_id[i]);
      rv = pthread_join(thread_id[i], (void **)&status);
      check_error(rv, "Join thread");
      if (status==PTHREAD_CANCELED)  // 查看终止原因
         printf("thread %d canceled %lx\n", i, thread_id[i]);
      else 
         printf("thread %d was not canceled\n", i);
   }
   return 0;
}
