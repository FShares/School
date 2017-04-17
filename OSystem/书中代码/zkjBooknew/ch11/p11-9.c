#include <sys/sem.h>
int open_semaphore_set( key_t keyval, int numsems )
{
   int sid;
   if (!numsems)  // 我们要求不论创建还是获得信号量都必须指明集合中信号量的个数
      return(-1);
   if((sid = semget( keyval, numsems, IPC_CREAT | 0660 )) == -1)
      return(-1);
   else
      return(sid);
}
