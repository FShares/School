#include "p11-12.h"

int main(void) /* �ͻ����� */
{
    struct exchange *shm;
    int shmid, producer_ok,consumer_ok,i;

    /* ���ź���consumer��producer */
    consumer_ok = open_semaphore_set(key1, 1);
    //init_a_semaphore(consumer_ok, 0, 0);
    /* �����ź���producer */
    producer_ok = open_semaphore_set(key2, 1);
    //init_a_semaphore(producer_ok, 0, 0);

    /* ��ò�������Ϊ"shared"�Ĺ���洢�� */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* �ӹ���洢�ζ����������д�����ݣ����������*/
    while(1){
       semaphore_P(producer_ok);   /* �ȴ������������ */
       /* �������ݣ�����"end"����ѭ�� */
       printf("%d recieived:Sequence=%d,data=%s",getpid(), shm->seq, shm->buf);
       if (strncmp(shm->buf, "end", 3) == 0)
          break;
       semaphore_V(consumer_ok);  /* �÷�������������� */        
    }
    /* ���빲��洢�� */
    shmdt(shm);
    semaphore_V(consumer_ok);  /* �÷�������������� */        
    exit(0);
}
