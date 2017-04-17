#include "ch13.h"
typedef struct barrier_struct {  //barrier数据结构
   int             valid;           //合法初始化标志
   pthread_cond_t   cv;             //条件变量
   pthread_mutex_t  mtx;            //相连的互斥变量
   int   predicate;                 //条件谓词,相同的栅栏同步点具有相同的值
   int   barrier_val;               //要等待的线程个数
   int   blocked_threads;           //已到达的线程个数
} barrier_t;                             
/* 用于保护barrier初始化的互斥变量 */
pthread_mutex_t barrier_init_mutex = PTHREAD_MUTEX_INITIALIZER;
#define BARRIER_VALID 546731      //barrier初始化标志
/* barrier b初始化函数 */
int barrier_init(barrier_t *b, int val)
{
   int rv;
   /* 申请barrier_init_mutex,使得每次只允许一个线程进行初始化 */
   if ((rv=pthread_mutex_lock(&barrier_init_mutex))!=0) 
      return (rv);   //上锁出错
   if (b->valid == BARRIER_VALID) { // 已进行过初始化，此次为重新初始化
      /* 获得用于栅栏和条件变量的互斥变量 */
      if ((rv=pthread_mutex_lock(&b->mtx))!=0){ 
         pthread_mutex_unlock(&barrier_init_mutex); 
         return(rv);
      }
      if (b->blocked_threads !=0 ){// 该barrier还有需等待的线程，返回错误
         pthread_mutex_unlock(&b->mtx);
         pthread_mutex_unlock(&barrier_init_mutex);
         return(EBUSY);
      }
      /* 重置barrier计数值后返回 */
      b->barrier_val=val;
      if ((rv=pthread_mutex_unlock(&b->mtx))!=0) {
         pthread_mutex_unlock(&barrier_init_mutex);
         return(rv);
      }
   }else {  // 首次初始化
      if ((rv=pthread_mutex_init(&b->mtx, NULL))!=0)
         return (rv); 
      if ((rv=pthread_cond_init(&b->cv, NULL)) !=0) {
         pthread_mutex_unlock(&barrier_init_mutex);
         return (rv);
      }
      b->barrier_val=val;
      b->blocked_threads =0;
      b->predicate =0;
      b->valid = BARRIER_VALID;
   }
   if ((rv=pthread_mutex_unlock(&barrier_init_mutex))!=0) // 释放锁，然后返回
      return (rv);
   return (0);
}  
  
/* 栅栏等待函数 */
int barrier_wait(barrier_t *b)
{
   int rv, predicate;
   if (b->valid != BARRIER_VALID) // 检查栅栏的合法性
      return(EINVAL);             // 栅栏未初始化错误
   if ((rv=pthread_mutex_lock(&b->mtx)) != 0) //申请用于栅栏和条件变量的互斥变量
      return (rv);     // 上锁出错
   predicate = b->predicate;  // 保存本次同步谓词值
   b->blocked_threads++;       // 增加到达线程计数
   if (b->blocked_threads == b->barrier_val) {  // 这是最后到达的线程
      /* 为下次同步重置栅栏值 */
      b->predicate += 1;                     
      b->blocked_threads = 0; 
      /* 唤醒所有受阻的线程 */
      if ((rv=pthread_cond_broadcast(&b->cv))!= 0) { 
          pthread_mutex_unlock(&b->mtx); // 广播出错,释放互斥变量后返回
          return(rv);  
      }
   }else{              // 这是先到达的线程
      /* 等待，直到所有线程都已到达 */
      while (b->predicate == predicate){
         rv = pthread_cond_wait(&b->cv, &b->mtx);
         if ((rv!=0)&&(rv!=EINTR)){
            pthread_mutex_unlock(&b->mtx);
            return(rv);  // 条件等待出错,释放互斥变量后返回
         }
      }
   }
   /* 栅栏同步结束，释放用于栅栏和条件变量的互斥变量 */
   if ((rv=pthread_mutex_unlock(&b->mtx))!=0)
      return(rv);   // 释放锁出错
   return(0);  // 正常返回
}
