#include "ch06.h"
#include "p6-3.c"  //pr_exit()

int zero=0;

int main(void)
{
   pid_t pid;
   int status;

   if ((pid = fork()) == 0)  /* �����ӽ���1 */
      exit(0);               /* �ӽ���1�����˳� */
   if ((pid = fork()) == 0)  /* �����ӽ���2 */
      abort();      /* �ӽ���2����SIGABRT�ź��˳� */
   if ((pid = fork()) == 0) {   /* �����ӽ���3 */
      status/=zero;   /* �ӽ���3��0����������SIGFPE�ź��˳� */
      exit(0);
   }
   while ((pid = wait(&status)) >= 0) /* �ȴ��ӽ���  */
      pr_exit(status, pid);
   perror("wait over");
   exit(EXIT_SUCCESS);
}
