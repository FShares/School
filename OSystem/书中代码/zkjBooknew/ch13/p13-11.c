#include "ch13.h"
typedef struct job_sync_data {
   int job_count;            //作业数
   pthread_mutex_t mtx;     //用于保护job_count
   pthread_cond_t cond;     //用于通知job_count的改变
} job_sync_data; 
job_sync_data job_sync = {
              0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
struct job {
   int job_id;
   void * work_ptr;
};
extern struct job *job_dequeue();          //从作业队列中提取一个作业
extern void procee_job(struct job *ptr);  //处理一个作业
void worker_thread()
{
   struct job *curr_job;
   int rv;
   for(; ;){
      /* 获得条件变量相连的互斥变量 */
      rv=pthread_mutex_lock(&job_sync.mtx);  
      check_error(rv, "mutex lock");
      /* 测试有否作业，如果没有则等待。条件变量等待会释放相连的互斥变量以便其它线程
         能够放置作业于队列之中。从条件变量等待返回之前会重新获得该互斥变量 */
      while (job_sync.job_count == 0)
         pthread_cond_wait(&job_sync.cond, &job_sync.mtx);
      curr_job=job_dequeue(); // 得到作业
      if (curr_job != NULL) 
         job_sync.job_count--; 
      // 释放相连的互斥变量
      rv=pthread_mutex_unlock(&job_sync.mtx);
      check_error(rv, "mtx_unlock failed");
      // 处理作业
      procee_job(curr_job); 
   }
}
