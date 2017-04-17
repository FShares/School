#include "ch11.h"
union semun {  /* 说明semun结构 */
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};
/* 删除指定的信号量集合 */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)
/* 给指定的信号量赋初值 */
void init_a_semaphore( int sid, int semnum, int initval)
{
   union semun semopts;    
   semopts.val = initval;
   semctl( sid, semnum, SETVAL, semopts);
}
/* 给指定的信号量集合赋初值 */
void init_all_semaphore( int sid, int val_array[])
{
   union semun semopts; 
   semopts.array = val_array;
   semctl( sid, 0, SETALL, semopts);
}
/* 改变信号量集合的访问权限,权限参数必须是形如"660"的字符串 */
int changemode(int sid, char *mode)
{
   int rc;
   union semun semopts;    
   struct semid_ds mysemds;
   semopts.buf = &mysemds;    /* 使semopts.buf 指向我们自己定义的缓冲区 */
   /* 获得内部数据结构的当前值 */
   if ((rc = semctl(sid, 0, IPC_STAT, semopts)) == -1)
      return -1;
   sscanf(mode, "%o", &semopts.buf->sem_perm.mode); /* 改变访问权限 */
   /* 更新内部数据结构 */
   return(semctl(sid, 0, IPC_SET, semopts));
}
