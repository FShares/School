#include "ch06.h"
int main (void)
{
   pid_t pid;
   if ((pid = fork()) < 0)
      err_exit("fork error");
   else if (pid == 0) {	            /* 第一个子进程 */
      if ((pid = fork()) < 0) 	    /* 再次派生一个子进程 */
         err_exit("fork error ");
      else if (pid > 0) {
         printf("child exit\n");
         exit(EXIT_SUCCESS);	      /*  终止第一次派生的子进程 */
      }
      /*  这是第二个子进程.当父进程执行exit后,它被init继承. */
      sleep(2);                 /* 在此做需子进程做的工作  */
      printf("grandchild's parent pid = %d\n", getppid ());
      exit(EXIT_SUCCESS);
   }
   if (waitpid(pid, NULL, 0) != pid) 	    /*  等待第一个子进程  */
      err_exit("waitpid error");
   printf ("parent exit\n");
   exit(EXIT_SUCCESS);
}
