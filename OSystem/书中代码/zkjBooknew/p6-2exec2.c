#include "ch06.h"
char *env_init[]={"USER=unknow","PATH=/tmp",NULL};
char *path = "/home/user1/Desktop/zkjBook/ch06/echoall";
char *myargv[]={"echoall","argv1","argv2","argv3",NULL};
char *dateargv[]={"date",NULL};
char *lsargv[]={"ls","-l",NULL};
char *geditargv[]={"gedit","file123",NULL};
int main(int argc, char *argv[])
{
   pid_t pid;
   if ((pid=fork()) < 0)  
      err_exit ("fork error");
   else if (pid == 0){ 
      execl("/bin/ls", "ls", "-l", "..", (char *)0);
      //execlp("ls", "ls", "-l", "..", (char *)0);
   }
   else { 
      printf("father OK!\n");
   }
      exit(EXIT_SUCCESS);  
}
