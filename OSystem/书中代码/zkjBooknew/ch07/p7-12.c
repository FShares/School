#include "ch07.h"
volatile pid_t pkid;
sig_atomic_t killed=0;
sigjmp_buf again;
void sig_handler(int sig, siginfo_t *sip, void *extra)
{
    printf ("%d got a signal: %d, ", getpid(), sig);
    fflush(stdout); 
    psignal(sig, "");
    if (sip->si_code == SI_USER){
        printf("\tsi_code %d, signal was sened by kill(), sender is %d\n",
                 sip->si_code, sip->si_pid);
        return;
    }
    printf ("\tsi_code %d, ", sip->si_code);
    switch (sig){  /* 对不同的信号，根据si_code的值对信号原因进行不同的判别 */
    case SIGFPE: 
       if (sip->si_code==FPE_INTDIV)
          printf ("integer divided by zero");
       else if (sip->si_code==FPE_FLTDIV)
          printf ("floating point divided by zero");
       else /* … 其它情形 */
          printf ("overflow or something else");
       printf (" at address %x\n", sip->si_addr);
       siglongjmp(again, 1); /* 返回时跳过出错点 */
       break;
    case SIGSEGV: 
       if (sip->si_code == SEGV_MAPERR)
           printf ("unmapped address:");
       else
           printf ("unprivileged access address:");
       printf("%x\n", sip->si_addr);
       exit(0);   /* 这是最后发送的信号，程序从这里终止运行 */
    case SIGCHLD:
       if (sip->si_code == CLD_KILLED)
           printf("\tChild %d was killed\n",sip->si_pid);
       else 
           printf("\tChild exited with exit_status: %d\n",sip->si_status);
       killed = 1;         /* 设置信号处理完毕标志 */
       break;
    default:
       printf("others\n");
       exit(0);
   }
}
void (*fun)(int)=NULL;   /* 悬空的函数指针 */
int a, b=0;
int main(void)
{
   struct sigaction sa;
   /* 设置信号句柄 */
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_SIGINFO;         /* 使用带三个参数的信号句柄 */
   sa.sa_sigaction = sig_handler;
   sigaction(SIGCHLD, &sa, 0);
   sigaction(SIGFPE, &sa, 0);
   sigaction(SIGSEGV, &sa, 0);
   /* 创建一个子进程,然后kill它 */ 
   if (pkid = fork()){     /* 父进程 */
       printf("I am father,My pid=%d. \n",getpid());
       printf("I forked and killed a child whose pid is %d\n", pkid);
       kill(pkid,SIGTERM); 
       while (!killed);              /* 等待直到子进程退出 */
       kill(getpid(),SIGFPE);
       if (sigsetjmp(again,1))      /* 设置非局部控制转移环境 */
          goto L1;
       a=a/b;            /* 浮点异常后将从信号句柄返回到上一语句 */ 
L1:
      (*fun)(a);        /* 空指针将导致函数调用产生段错, 信号句柄不返回 */
   } else               /* 子进程 */
       while(1);        /* 子进程等待被kill */
}
