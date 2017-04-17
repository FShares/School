#include "ch07.h"
int main(void)
{
    sigset_t base_mask, waiting_mask, oldmask;
    int sig;
     /* �����û����ж�. */
    sigemptyset (&base_mask);
    sigaddset (&base_mask, SIGQUIT);
    sigaddset (&base_mask, SIGINT);
    if (sigprocmask (SIG_BLOCK, &base_mask, &oldmask)<0 )
       err_exit("SIG_BLOCK error");
    printf(" I have blocked SIGQUIT and SIGINT, and\n you can try "
           "to send these two signals and wait for my reply.\n");
    sleep(10);
     /* ��һ�����,�鿴�Ƿ��������ź�. */
    printf("Let me see if there is any pending signal.\n");
    sigpending (&waiting_mask);
    for ( sig=1;sig<NSIG;sig++)
       if (sigismember (&waiting_mask, sig)){ 
          psignal(sig,"There is a pending signal" );
	       /* �Ը��ź�������Ӧ... */
       }
     /* �ָ��ź�����,�⽫�ſ�SIGINT��SIGTSTP */
    if (sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
       err_exit("SIG_SETMASK error");
    /* ������ź�,����Ĵ��벻��ִ�� */
    printf("Ther is no suspending signal. BYE!\n");	
    exit(EXIT_SUCCESS);
}
