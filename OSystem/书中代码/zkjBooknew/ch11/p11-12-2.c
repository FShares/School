#include "p11-12.h"

int main(void) /* 服务程序 */
{
    struct exchange *shm;
    int producer_ok,consumer_ok,i;
    int shmid;
    char readbuf[BUFSIZ];

    /* 创建信号量consumer和producer */
    consumer_ok = open_semaphore_set(key1, 1);
    producer_ok= open_semaphore_set(key2, 1);
    init_a_semaphore(consumer_ok, 0, 1);  /* 禁止消费 */
    init_a_semaphore(producer_ok, 0, 0);  /* 允许生产 */

    /* 获得并连接名为"shared"的共享存储段 */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* 从标准输入读数据并写至共享存储段 */
    for ( i=0; ; i++ ) {
         /* 读入数据 */
        semaphore_P(consumer_ok);   /* 等待客户进程释放共享存储段 */
        printf("Enter some text:");
        fgets(readbuf,BUFSIZ,stdin);
         /* 填充共享存储缓冲 */
        shm->seq = i;
        sprintf(shm->buf, "%s",readbuf);
        semaphore_V(producer_ok);  /* 允许客户进程取数据 */
        if (strncmp(readbuf, "end", 3) == 0 )
            break;
    }
    semaphore_P(consumer_ok); /* 等待客户进程消费完毕 */
    /* 删除信号量 */
    rm_semaphore(producer_ok);
    rm_semaphore(consumer_ok);

    /* 分离并删除共享存储段 */
    shmdt(shm);
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
    exit(0);
}
