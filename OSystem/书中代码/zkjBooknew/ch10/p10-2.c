#include "filelock.h"
const char *test_file="/tmp/test_lock";
int main(void)
{
   char *strw = "set write lock on region", *strr = "set read lock on region";
   int fd, bytes_count;
   fd = open(test_file, O_RDWR|O_CREAT, 0666);   /* 打开文件 */
   if(fd<0) 
      err_exit("Unable to open file");
   for (bytes_count = 0; bytes_count<100; bytes_count++)  /* 写入数据 */
      write(fd, "A", 1);              
   if (fork()!=0) {     /* 父进程 */
      /* 在区域[10-29]设置共享读锁 */
      if (SET_LOCK (fd, F_RDLCK, 10, SEEK_SET, 20)<0)
         fprintf(stderr,"%d %s [10-29] failed\n", getpid(),strr);
      else
         fprintf(stderr,"%d %s [10-29] succeed\n",getpid(),strr);
      /* 在区域[40-49]设置互斥写锁 */
      if (SET_LOCK (fd, F_WRLCK, 40, SEEK_SET, 10)<0)
         fprintf(stderr,"%d %s [40-49] failed\n", getpid(),strw);
      else
         fprintf(stderr,"%d %s [40-49] succeed \n",getpid(), strw);
      sleep(3);      /* 睡眠3秒以便子进程测试锁 */
      printf("%d close file\n",getpid());
      close(fd);
      exit(EXIT_SUCCESS);
   } else {         /* 子进程 */
      pid_t mypid=getpid(); 
      sleep(1);     /* 让父进程先运行 */
      /* 对区域[10-14]设置读锁，与父进程设置的读锁部分重叠，可成功 */
      if (SET_LOCK (fd, F_RDLCK, 10, SEEK_SET, 5)<0) 
         fprintf(stderr,"%d %s [10-14] failed\n", mypid, strr);
      else 
         fprintf(stderr, "%d %s [10-14] succeed\n", mypid, strr);    
      /* 对区域[15-20]加写锁，与父进程设置的读锁部分重叠，不会成功 */    
      if (SET_LOCK (fd, F_WRLCK, 15,SEEK_SET,6)<0) 
         fprintf(stderr,"%d %s [15-20] failed\n", mypid, strw);
      else 
        fprintf(stderr, "%d %s [15-20]\n", mypid, strw);
      /* 对区域[40-49]加读锁，与父进程设置的写锁重叠，不会成功 */
      if (SET_LOCK (fd, F_RDLCK, 40, SEEK_SET, 10)<0) 
         fprintf(stderr,"%d %s [40-49] failed\n", mypid,strr);
      else 
         fprintf(stderr,"%d %s [40-49] succeed\n", mypid, strr);
      /* 对区域[41-60]加写锁并等待，与父进程设置的写锁重叠，等待父进程退出后才会成功 */   
      if (SET_LOCK_W(fd, F_WRLCK, 41, SEEK_SET, 20)<0) 
         fprintf(stderr,"%d %s [41-60] succeed\n", mypid, strw);
      else
         fprintf(stderr,"%d %s [41-60] succeed\n", mypid, strw);
      /* 对区域[0-60]解锁，将同时释放区域[10-14]的读锁和区域[41-60]的写锁 */
      if (un_lock (fd,0,SEEK_SET,69)<0) 
         fprintf(stderr,"%d unlock the region [0-69] failed\n", mypid);
      else 
         fprintf(stderr,"%d unlocked the region [0-69] succeed\n", mypid);
      fprintf(stderr,"Process %d end\n", mypid);    
      close(fd);
      exit(EXIT_SUCCESS);
   }
}
