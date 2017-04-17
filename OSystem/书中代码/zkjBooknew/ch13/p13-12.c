#include "ch13.h"
extern struct job *create_job();            //创建一个作业
extern void job_enqueue(struct job *ptr); //向作业队列添加一个作业
typedef struct job_sync_data {
   int job_count;            //作业数
   pthread_mutex_t mtx;     //用于保护job_count
   pthread_cond_t cond;     //用于通知job_count的改变
} job_sync_data;
extern job_sync_data job_sync;
void master_thread()
{
   struct job *new_job;
   int rv;
   for (; ;) {
      if ((new_job = create_job())== NULL)  // 创建下一个作业
         pthread_exit((void *)NULL);         // 没有进一步的工作则终止自己
      /* 获得相连的互斥变量 */
      rv=pthread_mutex_lock(&job_sync.mtx); 
      check_error(rv, "mutex lock");
      /* 添加新作业至作业队列 */
      job_enqueue(new_job);
      job_sync.job_count++;
      /* 向条件变量发信号唤醒一个线程 */
      rv = pthread_cond_signal(&job_sync.cond);
      check_error(rv,"cond_signal");  
      /* 释放相连的互斥变量 */
      rv=pthread_mutex_unlock(&job_sync.mtx);
      check_error(rv,"mtx_unlock");
   }
}
