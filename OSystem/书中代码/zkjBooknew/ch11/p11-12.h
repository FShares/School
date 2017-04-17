#include "ch11.h" 
#include "p11-11.c"   //semaphore_P()/semaphore_V()
#include "p11-9.c"    // open_semaphore_set()

/* 删除指定的信号量集合 */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)

struct exchange {
    char buf[BUFSIZ+80];    /* 需交换的数据*/
    int seq;                /* 客户填入的顺序号 */
};

/* semun结构 */
union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};

key_t key1=123,key2=456;

/* 创建/打开共享存储段，连接它到用户地址空间，返回它在用户空间的地址 */
unsigned char *shminit(key_t key, int *shmid)
{
    unsigned char *retval;
    if((*shmid = shmget(key,sizeof(struct exchange),0666|IPC_CREAT))== -1)
        err_exit("shmget");
    if((retval = shmat(*shmid,(unsigned char *)0,0)) == (unsigned char *)-1 )
        err_exit("shmmat");
    return retval;
}

/* 给指定的信号量赋初值 */
void init_a_semaphore( int sid, int semnum, int initval)
{
    union semun semopts;    
    semopts.val = initval;
    semctl( sid, semnum, SETVAL, semopts);
}



