#include "ch06.h"
#include "p6-3.c" //pr_exit()

/*  parse--分解buf中的命令为独立的参数  */
void parse(char *buf, char *args[])
{
   int i=0;
   while (*buf != '\0') {
      /* 用空字符'\0'替代空白字符使得前一参数以空字符结束  */       
      args[i++]=buf;
      while ((*buf!=' ')&&(*buf!='\t')&&(*buf!='\n')) buf++;
      while ((*buf==' ')||(*buf=='\t'||(*buf=='\n'))) *buf++ = '\0';
   }
   args[i]='\0';
}

/*  execute--派生一子进程执行此程序  */
void execute(char *args[])
{
   int pid, status;
   /*  创建一子进程  */
   if ((pid=fork()) <0) 
      err_exit("fork");
   /*  子进程执行if内的代码  */
   if (pid==0) {
      execvp(*args,args);
      err_exit("execvp");
   } 
   /*  父进程等待子进程完成  */
   waitpid(pid, &status, 0);
   pr_exit(status,pid);
}
int main(void)
{
   char buf[1024];
   char *args[64], *cp;

   for (;;) {
     printf("Command: ");   // 给出提示符
     cp = fgets (buf, sizeof(buf), stdin);    //读入命令
     if (cp == (char *)NULL || *cp == '\n'){  // 空行表示退出
        printf("quit\n");
        exit(EXIT_SUCCESS);
     }
     /*  分解字符串为参数  */
     parse(buf, args);
     /*  执行命令  */
     execute(args);
   }
}

