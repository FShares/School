#include "ch06.h"

int global = 5;

int main(void)
{
   pid_t pid;
   char *string = "I am parent";
   int local = 10;

   printf(" before fork--- ");
   if ((pid = fork()) < 0)  /* fork调用失败 */  
      err_exit("fork");
   if (pid == 0){            /* 子进程 */
      string = "I am child";
      printf("%s, my pid=%d: global=%d, local=%d\n",
              string, getpid(), global, local);
      global ++;
   } else {           /* 父进程 */
      printf("%s, my pid=%d: global=%d, local=%d\n ",
              string, getpid(), global, local);
      local++;
   }
   printf("At join point, %s: global=%d, local=%d\n", string, global, local);
   exit(EXIT_SUCCESS);
}
