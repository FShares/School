#include "ch06.h"
int main (void)
{
   pid_t pid;
   if ((pid = fork()) < 0)
      err_exit("fork error");
   else if (pid == 0) {	            /* ��һ���ӽ��� */
      if ((pid = fork()) < 0) 	    /* �ٴ�����һ���ӽ��� */
         err_exit("fork error ");
      else if (pid > 0) {
         printf("child exit\n");
         exit(EXIT_SUCCESS);	      /*  ��ֹ��һ���������ӽ��� */
      }
      /*  ���ǵڶ����ӽ���.��������ִ��exit��,����init�̳�. */
      sleep(2);                 /* �ڴ������ӽ������Ĺ���  */
      printf("grandchild's parent pid = %d\n", getppid ());
      exit(EXIT_SUCCESS);
   }
   if (waitpid(pid, NULL, 0) != pid) 	    /*  �ȴ���һ���ӽ���  */
      err_exit("waitpid error");
   printf ("parent exit\n");
   exit(EXIT_SUCCESS);
}
