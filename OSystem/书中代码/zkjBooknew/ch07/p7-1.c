#include "ch07.h"
volatile sig_atomic_t usr_interrupt = 0;   /* ��������SIGUSR1�ź�ʱ���ô˱��� */
void sig_usr(int sig)                  /* SIGUSR1�źŲ����� */
{
   usr_interrupt = 1;
}
void child_function(void)        /* �ӽ���ִ�д˺��� */
{
   printf("I'm here!  My pid is %d.\n", (int)getpid());
   kill(getppid(), SIGUSR1);     /* ֪ͨ������ */
   /* ����ִ�� */
   puts("Bye, now....");
   exit(EXIT_SUCCESS);
}
int main(void)
{
   pid_t child_id;     
   signal (SIGUSR1, sig_usr);  /* �����źž�� */
   child_id = fork ();          /* �����ӽ��� */
   if (child_id == 0)           /* �ӽ��� */
      child_function();         /* �ӽ��̲����� */
   while (!usr_interrupt) ;    /* �ȴ��ӽ��̷����ź� */  
   puts ("That's all!");       /* �յ��źź����ִ�� */
   return 0;
}

