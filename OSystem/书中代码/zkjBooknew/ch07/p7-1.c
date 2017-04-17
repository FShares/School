#include "ch07.h"
volatile sig_atomic_t usr_interrupt = 0;   /* 当捕获了SIGUSR1信号时设置此变量 */
void sig_usr(int sig)                  /* SIGUSR1信号捕获函数 */
{
   usr_interrupt = 1;
}
void child_function(void)        /* 子进程执行此函数 */
{
   printf("I'm here!  My pid is %d.\n", (int)getpid());
   kill(getppid(), SIGUSR1);     /* 通知父进程 */
   /* 继续执行 */
   puts("Bye, now....");
   exit(EXIT_SUCCESS);
}
int main(void)
{
   pid_t child_id;     
   signal (SIGUSR1, sig_usr);  /* 建立信号句柄 */
   child_id = fork ();          /* 创建子进程 */
   if (child_id == 0)           /* 子进程 */
      child_function();         /* 子进程不返回 */
   while (!usr_interrupt) ;    /* 等待子进程发送信号 */  
   puts ("That's all!");       /* 收到信号后继续执行 */
   return 0;
}

