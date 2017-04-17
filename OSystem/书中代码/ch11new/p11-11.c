/* P����--��ͼ����һ�ؼ��� */
//void semaphore_P(int sem_id)
int semaphore_P(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = -1;          /* P�������ź���ֵ���� */
   sb.sem_flg = SEM_UNDO;   /* �������������ź�������*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,"semaphore_P failed\n");
       return(0);
   }
   return(1);
}
/* V����--�뿪�ؼ��� */
//void semaphore_V(int sem_id)
int semaphore_V(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = 1;           /* V�������ź���ֵ���� */
   sb.sem_flg = SEM_UNDO;   /* �������������ź�������*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,"semaphore_V failed\n");
       return(0);
   }
   return(1);
}
