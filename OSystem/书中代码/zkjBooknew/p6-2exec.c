#include "ch06.h"
char *env_init[]={"USER=unknow","PATH=/tmp",NULL};
char *path = "/home/user1/Desktop/zkjBook/ch06/echoall";
char *myargv[]={"echoall","argv1","argv2","argv3",NULL};
char *dateargv[]={"date",NULL};
char *lsargv[]={"ls","-l",NULL};
char *geditargv[]={"gedit","file123",NULL};
int main(void)
{
   pid_t pid;
   if ((pid=vfork()) < 0)  
      err_exit ("vfork error");
   else if (pid == 0){ /* 子进程 */
      //if (execle(path, "echoall", "arg1", "ARG2", (char *)0, env_init) < 0)
	//if (execle(path, "echoall", "arg1", "ARG2", "argMe", NULL, env_init) < 0)
          //err_exit("execle error");
	//if (execl(path, "echoall", "arg11", "ARG22", "argMeMe", NULL) < 0)
          //err_exit("execle error");
	//if (execve(path, myargv, env_init) < 0)
          //err_exit("execle error");
	//if (execvp("date", dateargv) < 0)
          //err_exit("execle error");
	//if (execvp("ls", lsargv) < 0)
          //err_exit("execle error");
	//if (execvp("gedit", geditargv) < 0)
          //err_exit("execle error");
	//if (execlp("gedit", "gedit","file123",(char *)0 ) < 0)
          //err_exit("execle error");
	if (execlp("ls", "ls", "-l", (char *)0 ) < 0)
          err_exit("execle error");
      }
   else { 
      if ((pid=vfork()) < 0)  
         err_exit("vfork error");
      else if (pid == 0){ /* 子进程 */
         if (execlp("./echoall", "echoall", "only one arg", (char *)0)<0)
            err_exit("execle error");
      }
   
      exit(EXIT_SUCCESS);
   }
}
