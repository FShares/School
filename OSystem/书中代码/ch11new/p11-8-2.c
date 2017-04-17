#include "ch11.h"
#define SHMSZ     27
int main(void)
{
    int shmid;
    key_t key;
    char *shm, *s;
    /* �����Ϊ��785���Ĺ���洢�� */
    key = 785; 
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) 
        err_exit("shmget");
    /* ���Ӹù���洢�� */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
        err_exit("shmat");
    /* �ӹ���洢�ζ����������д�����ݣ����������*/
    for (s = shm; *s != '\0'; s++)
        putchar(*s);
    putchar('\n');
    exit(0);
}
