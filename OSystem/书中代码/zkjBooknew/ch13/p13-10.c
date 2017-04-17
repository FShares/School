#include "ch13.h"
#include <sys/ipc.h>
#include <sys/shm.h>
typedef struct sync_struct {
pthread_cond_t  cond;          
pthread_mutex_t  mtx;          
int pred;
} sync_struct_t;
#define KEY  1234
/* 创建进程共享全局条件变量和互斥变量 */
create_pshared_cond_sync_data (sync_struct_t  *sync_data)
{
   pthread_mutexattr_t mtx_attr;
   pthread_condattr_t cond_attr;
   int rv, shmid;

   /* 初始化属性对象 */
   rv =pthread_mutexattr_init(&mtx_attr);
   check_error(rv, "mutexattr_init");
   rv =pthread_condattr_init(&cond_attr);
   check_error(rv, "condattr_init");

   /* 设置属性对象的进程共享属性 */
   rv=pthread_mutexattr_setpshared(&mtx_attr, PTHREAD_PROCESS_SHARED);
   check_error(rv, "mutexattr_setpshared");
   rv=pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
   check_error(rv, "condattr_setpshared");

   /* 为同步变量sync_data分配共享存储空间 */
   if ((shmid=shmget(KEY, sizeof(sync_struct_t), 066|IPC_CREAT))<0)
      err_exit("shmget");
   if ((sync_data=(sync_struct_t *)shmat(shmid, NULL, 0))==(sync_struct_t *)-1)
      err_exit("shmat");

   /* 初始化互斥变量和条件变量 */
   rv=pthread_mutex_init(&sync_data->mtx, &mtx_attr);
   check_error(rv, "mutex_init")
   rv=pthread_cond_init(&sync_data->cond, &cond_attr);
   check_error(rv, "cond_init");

   /* 销毁属性对象 */
   rv = pthread_mutexattr_destroy(&mtx_attr);  
   check_error(rv, "mutexattr_destroy");
   rv = pthread_condattr_destroy(&cond_attr);   
   check_error(rv, "condattr_destroy");
   return;
}
