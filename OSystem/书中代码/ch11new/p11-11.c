/* P操作--企图进入一关键区 */
//void semaphore_P(int sem_id)
int semaphore_P(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = -1;          /* P操作－信号量值减少 */
   sb.sem_flg = SEM_UNDO;   /* 如果死亡，解除信号量请求*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,"semaphore_P failed\n");
       return(0);
   }
   return(1);
}
/* V操作--离开关键区 */
//void semaphore_V(int sem_id)
int semaphore_V(int sem_id)
{
   struct sembuf sb;
   sb.sem_num = 0;
   sb.sem_op = 1;           /* V操作－信号量值增加 */
   sb.sem_flg = SEM_UNDO;   /* 如果死亡，解除信号量请求*/
   if (semop(sem_id, &sb, 1) == -1){
       fprintf(stderr,"semaphore_V failed\n");
       return(0);
   }
   return(1);
}
