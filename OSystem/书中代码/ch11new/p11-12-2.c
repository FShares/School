#include "p11-12.h"

int main(void) /* ������� */
{
    struct exchange *shm;
    int producer_ok,consumer_ok,i;
    int shmid;
    char readbuf[BUFSIZ];

    /* �����ź���consumer��producer */
    consumer_ok = open_semaphore_set(key1, 1);
    producer_ok= open_semaphore_set(key2, 1);
    init_a_semaphore(consumer_ok, 0, 1);  /* ��ֹ���� */
    init_a_semaphore(producer_ok, 0, 0);  /* �������� */

    /* ��ò�������Ϊ"shared"�Ĺ���洢�� */
    shm = (struct exchange *)shminit(ftok("shared",0),&shmid);

    /* �ӱ�׼��������ݲ�д������洢�� */
    for ( i=0; ; i++ ) {
         /* �������� */
        semaphore_P(consumer_ok);   /* �ȴ��ͻ������ͷŹ���洢�� */
        printf("Enter some text:");
        fgets(readbuf,BUFSIZ,stdin);
         /* ��乲��洢���� */
        shm->seq = i;
        sprintf(shm->buf, "%s",readbuf);
        semaphore_V(producer_ok);  /* ����ͻ�����ȡ���� */
        if (strncmp(readbuf, "end", 3) == 0 )
            break;
    }
    semaphore_P(consumer_ok); /* �ȴ��ͻ������������ */
    /* ɾ���ź��� */
    rm_semaphore(producer_ok);
    rm_semaphore(consumer_ok);

    /* ���벢ɾ������洢�� */
    shmdt(shm);
    shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
    exit(0);
}
