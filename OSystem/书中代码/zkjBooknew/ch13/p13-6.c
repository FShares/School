#include "ch13.h"
#include <sys/shm.h>
#include "xmalloc.c"
/* 创建一个动态分配空间、具有定制属性的互斥变量 */
pthread_mutex_t *mutex_customized (int shared, int type, int key)
{
   int rv;
   key_t shmid;
   pthread_mutex_t *mtx;
   pthread_mutexattr_t mtxattr;  // 互斥变量属性对象
   /* 初始化互斥变量属性对象 */
   rv = pthread_mutexattr_init (&mtxattr);
   check_error(rv, "mutexattr_init ");
   /* 设置共享属性 */
   rv = pthread_mutexattr_setpshared(&mtxattr, shared);
   check_error(rv, " mutexattr_setpshared ");
   /* 设置类型属性，在有的系统上需要明确定义特征测试宏_GNU_SOUCE */
   rv = pthread_mutexattr_settype (&mtxattr, type);
   check_error(rv, "mutexattr_settype");
   /* 为互斥变量分配共享存储空间 */
   if (shared == PTHREAD_PROCESS_PRIVATE)
      mtx = (pthread_mutex_t *)xmalloc(sizeof(pthread_mutex_t));     
   else {  // 进程共享互斥变量分配在共享存储中
      shmid = shmget(key, sizeof(pthread_mutex_t), 0666|IPC_CREAT);
      if (shmid == -1) 
          err_exit("shmget error");
      mtx = (pthread_mutex_t *)shmat(shmid, (char *)0, 0);
      if ((int)mtx == -1) 
         err_exit("shmget error");
   }
   /* 用属性对象初始化mtx */
   rv = pthread_mutex_init(mtx, &mtxattr);
   check_error(rv, "mutex_init ");
   /* 立即销毁不再需要的属性对象 */
   rv=pthread_mutexattr_destroy(&mtxattr);
   check_error(rv, "mutexattr destroy ");
   return (mtx);
} 
#define KEY 8125
pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;  // 静态初始化的进程私有互斥变量
pthread_mutex_t mtx2;       // 动态初始化的进程私有互斥变量
pthread_mutex_t *mtx3;      // 进程共享互斥变量
int main(void)
{
   int rv;
   // ...
   rv = pthread_mutex_init (&mtx2, NULL); // 初始化mtx2为系统缺省互斥变量
   /*初始化mtx3为定制的进程共享递归互斥变量*/
   mtx3 = mutex_customized(PTHREAD_PROCESS_SHARED,
                            PTHREAD_MUTEX_RECURSIVE,KEY);
   // ...应用程序的其它代码
   /* 销毁mtx2 */
   rv = pthread_mutex_destroy(&mtx2);
   check_error(rv, "mutex_destroy: mtx2");
   pthread_exit(NULL);
}
