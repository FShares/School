#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    char c, *shm, *s;
    int shmid;
    /* 创建名为"785"的共享存储段 */
    if ((shmid = shmget(785, SHMSZ, IPC_CREAT|0666)) < 0) 
        err_exit("shmget");
    /* 连接共享存储段至进程的数据空间 */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* 写一串字母至共享存储给另一个进程 */
    s = shm;
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = '\0';
    exit(0);
}
