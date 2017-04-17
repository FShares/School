#include "ch07.h"
int main(void)
{
    sigset_t base_mask, waiting_mask, oldmask;
    int sig;
     /* 阻塞用户的中断. */
    sigemptyset (&base_mask);
    sigaddset (&base_mask, SIGQUIT);
    sigaddset (&base_mask, SIGINT);
    if (sigprocmask (SIG_BLOCK, &base_mask, &oldmask)<0 )
       err_exit("SIG_BLOCK error");
    printf(" I have blocked SIGQUIT and SIGINT, and\n you can try "
           "to send these two signals and wait for my reply.\n");
    sleep(10);
     /* 过一会儿后,查看是否有悬挂信号. */
    printf("Let me see if there is any pending signal.\n");
    sigpending (&waiting_mask);
    for ( sig=1;sig<NSIG;sig++)
       if (sigismember (&waiting_mask, sig)){ 
          psignal(sig,"There is a pending signal" );
	       /* 对该信号做出回应... */
       }
     /* 恢复信号屏蔽,这将放开SIGINT和SIGTSTP */
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
       err_exit("SIG_SETMASK error");
    /* 如果有信号,下面的代码不会执行 */
    printf("Ther is no suspending signal. BYE!\n");	
    exit(EXIT_SUCCESS);
}
