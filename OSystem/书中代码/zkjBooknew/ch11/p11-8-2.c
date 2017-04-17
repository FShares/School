#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    int shmid;
    key_t key;
    char *shm, *s;
    /* 获得名为“785”的共享存储段 */
    key = 785; 
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
        err_exit("shmget");
    /* 连接该共享存储段 */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* 从共享存储段读服务进程所写的数据，并输出它们*/
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');
    exit(0);
}
