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
    switch (sig){  /* �Բ�ͬ���źţ�����si_code��ֵ���ź�ԭ����в�ͬ���б� */
    case SIGFPE: 
       if (sip->si_code==FPE_INTDIV)
          printf ("integer divided by zero");
       else if (sip->si_code==FPE_FLTDIV)
          printf ("floating point divided by zero");
       else /* �� �������� */
          printf ("overflow or something else");
       printf (" at address %x\n", sip->si_addr);
       siglongjmp(again, 1); /* ����ʱ��������� */
       break;
    case SIGSEGV: 
       if (sip->si_code == SEGV_MAPERR)
           printf ("unmapped address:");
       else
           printf ("unprivileged access address:");
       printf("%x\n", sip->si_addr);
       exit(0);   /* ��������͵��źţ������������ֹ���� */
    case SIGCHLD:
       if (sip->si_code == CLD_KILLED)
           printf("\tChild %d was killed\n",sip->si_pid);
       else 
           printf("\tChild exited with exit_status: %d\n",sip->si_status);
       killed = 1;         /* �����źŴ�����ϱ�־ */
       break;
    default:
       printf("others\n");
       exit(0);
   }
}
void (*fun)(int)=NULL;   /* ���յĺ���ָ�� */
int a, b=0;
int main(void)
{
   struct sigaction sa;
   /* �����źž�� */
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = SA_SIGINFO;         /* ʹ�ô������������źž�� */
   sa.sa_sigaction = sig_handler;
   sigaction(SIGCHLD, &sa, 0);
   sigaction(SIGFPE, &sa, 0);
   sigaction(SIGSEGV, &sa, 0);
   /* ����һ���ӽ���,Ȼ��kill�� */ 
   if (pkid = fork()){     /* ������ */
       printf("I am father,My pid=%d. \n",getpid());
       printf("I forked and killed a child whose pid is %d\n", pkid);
       kill(pkid,SIGTERM); 
       while (!killed);              /* �ȴ�ֱ���ӽ����˳� */
       kill(getpid(),SIGFPE);
       if (sigsetjmp(again,1))      /* ���÷Ǿֲ�����ת�ƻ��� */
          goto L1;
       a=a/b;            /* �����쳣�󽫴��źž�����ص���һ��� */ 
L1:
      (*fun)(a);        /* ��ָ�뽫���º������ò����δ�, �źž�������� */
   } else               /* �ӽ��� */
       while(1);        /* �ӽ��̵ȴ���kill */
}
