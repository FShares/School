#include "ch06.h"
#include "p6-3.c"  //pr_exit()

int zero=0;

int main(void)
{
   pid_t pid;
   int status;

   if ((pid = fork()) == 0)  /* 派生子进程1 */
      exit(0);               /* 子进程1正常退出 */
   if ((pid = fork()) == 0)  /* 派生子进程2 */
      abort();      /* 子进程2生成SIGABRT信号退出 */
   if ((pid = fork()) == 0) {   /* 派生子进程3 */
      status/=zero;   /* 子进程3因0作除数生成SIGFPE信号退出 */
      exit(0);
   }
   while ((pid = wait(&status)) >= 0) /* 等待子进程  */
      pr_exit(status, pid);
   perror("wait over");
   exit(EXIT_SUCCESS);
}
