#include "ch07.h"
static void sig_usr(int); 
int main(void)
{
   if(signal(SIGUSR1, sig_usr) == SIG_ERR) /* �����ź�SIGUSR1�ľ�� */
      err_exit ("can't catch SIGUSR1\n");
   for(; ;)
      pause();
}
static void sig_usr(int signo)       /* �ź�SIGUSR1�ľ�� */
{
   printf("received SIGUSR1\n");
   return;
}
