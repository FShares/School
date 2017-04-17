#include "ch11.h"
union semun {  /* ˵��semun�ṹ */
   int val;
   struct semid_ds *buf;
   unsigned short *array;
};
/* ɾ��ָ�����ź������� */
#define rm_semaphore(sid) semctl(sid, 0, IPC_RMID,0)
/* ��ָ�����ź�������ֵ */
void init_a_semaphore( int sid, int semnum, int initval)
{
   union semun semopts;    
   semopts.val = initval;
   semctl( sid, semnum, SETVAL, semopts);
}
/* ��ָ�����ź������ϸ���ֵ */
void init_all_semaphore( int sid, int val_array[])
{
   union semun semopts; 
   semopts.array = val_array;
   semctl( sid, 0, SETALL, semopts);
}
/* �ı��ź������ϵķ���Ȩ��,Ȩ�޲�������������"660"���ַ��� */
int changemode(int sid, char *mode)
{
   int rc;
   union semun semopts;    
   struct semid_ds mysemds;
   semopts.buf = &mysemds;    /* ʹsemopts.buf ָ�������Լ�����Ļ����� */
   /* ����ڲ����ݽṹ�ĵ�ǰֵ */
   if ((rc = semctl(sid, 0, IPC_STAT, semopts)) == -1)
      return -1;
   sscanf(mode, "%o", &semopts.buf->sem_perm.mode); /* �ı����Ȩ�� */
   /* �����ڲ����ݽṹ */
   return(semctl(sid, 0, IPC_SET, semopts));
}
