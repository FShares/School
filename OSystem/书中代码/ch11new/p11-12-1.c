#include "p11-12.h"

int main(void) /* 客户程序 */
{
    struct exchange *shm;
    int shmid, producer_ok,consumer_ok,i;

    /* 打开信号量consumer和producer */
    consumer_ok = open_semaphore_set(key1, 1);
    //init_a_semaphore(consumer_ok, 0, 0);
    /* 创建信号量producer */
    producer_ok = open_semaphore_set(key2, 1);
    //init_a_semaphore(producer_ok, 0, 0);

    /* 获得并连接名为"shared"的共享存储段 */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* 从共享存储段读服务进程所写的数据，并输出它们*/
    while(1){
       semaphore_P(producer_ok);   /* 等待数据生成完毕 */
       /* 处理数据，遇到"end"结束循环 */
       printf("%d recieived:Sequence=%d,data=%s",getpid(), shm->seq, shm->buf);
       if (strncmp(shm->buf, "end", 3) == 0)
          break;
       semaphore_V(consumer_ok);  /* 让服务进程生成数据 */        
    }
    /* 分离共享存储段 */
    shmdt(shm);
    semaphore_V(consumer_ok);  /* 让服务进程生成数据 */        
    exit(0);
}
