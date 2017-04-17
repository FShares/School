#include "ch11.h" 
#include "p11-11.c"   //semaphore_P()/semaphore_V()
#include "p11-9.c"    // open_semaphore_set()

/* ɾ��ָ�����ź������� */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)

struct exchange {
    char buf[BUFSIZ+80];    /* �轻��������*/
    int seq;                /* �ͻ������˳��� */
};

/* semun�ṹ */
union semun {
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};

key_t key1=123,key2=456;

/* ����/�򿪹���洢�Σ����������û���ַ�ռ䣬���������û��ռ�ĵ�ַ */
unsigned char *shminit(key_t key, int *shmid)
{
    unsigned char *retval;
    if((*shmid = shmget(key,sizeof(struct exchange),0666|IPC_CREAT))== -1)
        err_exit("shmget");
    if((retval = shmat(*shmid,(unsigned char *)0,0)) == (unsigned char *)-1 )
        err_exit("shmmat");
    return retval;
}

/* ��ָ�����ź�������ֵ */
void init_a_semaphore( int sid, int semnum, int initval)
{
    union semun semopts;    
    semopts.val = initval;
    semctl( sid, semnum, SETVAL, semopts);
}



