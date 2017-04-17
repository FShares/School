#include "filelock.h"
const char *test_file="/tmp/test_lock";
int main(void)
{
   char *strw = "set write lock on region", *strr = "set read lock on region";
   int fd, bytes_count;
   fd = open(test_file, O_RDWR|O_CREAT, 0666);   /* ���ļ� */
   if(fd<0) 
      err_exit("Unable to open file");
   for (bytes_count = 0; bytes_count<100; bytes_count++)  /* д������ */
      write(fd, "A", 1);              
   if (fork()!=0) {     /* ������ */
      /* ������[10-29]���ù������ */
      if (SET_LOCK (fd, F_RDLCK, 10, SEEK_SET, 20)<0)
         fprintf(stderr,"%d %s [10-29] failed\n", getpid(),strr);
      else
         fprintf(stderr,"%d %s [10-29] succeed\n",getpid(),strr);
      /* ������[40-49]���û���д�� */
      if (SET_LOCK (fd, F_WRLCK, 40, SEEK_SET, 10)<0)
         fprintf(stderr,"%d %s [40-49] failed\n", getpid(),strw);
      else
         fprintf(stderr,"%d %s [40-49] succeed \n",getpid(), strw);
      sleep(3);      /* ˯��3���Ա��ӽ��̲����� */
      printf("%d close file\n",getpid());
      close(fd);
      exit(EXIT_SUCCESS);
   } else {         /* �ӽ��� */
      pid_t mypid=getpid(); 
      sleep(1);     /* �ø����������� */
      /* ������[10-14]���ö������븸�������õĶ��������ص����ɳɹ� */
      if (SET_LOCK (fd, F_RDLCK, 10, SEEK_SET, 5)<0) 
         fprintf(stderr,"%d %s [10-14] failed\n", mypid, strr);
      else 
         fprintf(stderr, "%d %s [10-14] succeed\n", mypid, strr);    
      /* ������[15-20]��д�����븸�������õĶ��������ص�������ɹ� */    
      if (SET_LOCK (fd, F_WRLCK, 15,SEEK_SET,6)<0) 
         fprintf(stderr,"%d %s [15-20] failed\n", mypid, strw);
      else 
        fprintf(stderr, "%d %s [15-20]\n", mypid, strw);
      /* ������[40-49]�Ӷ������븸�������õ�д���ص�������ɹ� */
      if (SET_LOCK (fd, F_RDLCK, 40, SEEK_SET, 10)<0) 
         fprintf(stderr,"%d %s [40-49] failed\n", mypid,strr);
      else 
         fprintf(stderr,"%d %s [40-49] succeed\n", mypid, strr);
      /* ������[41-60]��д�����ȴ����븸�������õ�д���ص����ȴ��������˳���Ż�ɹ� */   
      if (SET_LOCK_W(fd, F_WRLCK, 41, SEEK_SET, 20)<0) 
         fprintf(stderr,"%d %s [41-60] succeed\n", mypid, strw);
      else
         fprintf(stderr,"%d %s [41-60] succeed\n", mypid, strw);
      /* ������[0-60]��������ͬʱ�ͷ�����[10-14]�Ķ���������[41-60]��д�� */
      if (un_lock (fd,0,SEEK_SET,69)<0) 
         fprintf(stderr,"%d unlock the region [0-69] failed\n", mypid);
      else 
         fprintf(stderr,"%d unlocked the region [0-69] succeed\n", mypid);
      fprintf(stderr,"Process %d end\n", mypid);    
      close(fd);
      exit(EXIT_SUCCESS);
   }
}
