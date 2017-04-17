#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    char c, *shm, *s;
    int shmid;
    /* ������Ϊ"785"�Ĺ���洢�� */
    if ((shmid = shmget(785, SHMSZ, IPC_CREAT|0666)) < 0) 
        err_exit("shmget");
    /* ���ӹ���洢�������̵����ݿռ� */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* дһ����ĸ������洢����һ������ */
    s = shm;
    for (c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = '\0';
    exit(0);
}
