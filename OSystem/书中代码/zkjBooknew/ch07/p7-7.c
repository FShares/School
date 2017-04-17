#include "ch07.h"
static volatile sig_atomic_t sigflag = 0;
static void sig_usr (int signo)
{
    psignal (signo, "   recieved");
}
static void sig_intr (int signo)
{
    psignal (signo, "   received");
    sigflag = 1;
}
void wait_for_signal (int sig, volatile sig_atomic_t *sflag)
{
    static sigset_t mask,oldmask;
    sigemptyset(&mask);     
    sigaddset(&mask,sig);
    /* 阻塞信号sig，并保存当前信号屏蔽 */
    if (sigprocmask(SIG_BLOCK,&mask,&oldmask)<0){
       printf("SIG_BLOCK error");
       exit(1);
    }
    sigdelset (&oldmask, SIGUSR1);   /* 这两行是为示例而加入的非必要代码 */
    sigdelset (&oldmask, SIGUSR2);
    while (!*sflag){                    /* 等待信号 */
       printf ("door opened\n");
       sigsuspend(&oldmask);       
       printf ("door closed\n");
    }
    *sflag = 0;
    if (sigprocmask(sig, &oldmask, NULL)<0)   /* 恢复信号屏蔽至原来的值 */
       printf("SIG_SETMASK error");
}
int main(void)
{
    pid_t pid;
    static sigset_t mask,oldmask;
    signal (SIGUSR1, sig_usr);
    signal (SIGUSR2, sig_usr);
    signal (SIGINT, sig_intr);
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);   /* 为示例目的先阻塞这两个信号 */
    sigaddset(&mask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK,&mask,&oldmask)<0){
       printf("SIG_BLOCK error");
       exit(1);
    }
    if ((pid = fork()) == 0) {     /* 子进程  */
       kill (getppid(), SIGUSR1);
       kill (getppid(), SIGUSR2);
       printf ("child ok");
       while (1);
    } else {             /* 父进程  */
       wait_for_signal (SIGINT, &sigflag);
       printf ("Now, I can do my work.  :)\n");
       kill (pid, SIGTERM);
    }
    exit(0);
}
