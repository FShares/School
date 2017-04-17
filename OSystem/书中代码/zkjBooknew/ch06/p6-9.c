#include "ch06.h" 

 /* 一个 process 代表一个进程.  */
typedef struct process
{
   struct process *next;       /* next process in pipeline */
   char **argv;                /* for exec */
   pid_t pid;                  /* process ID */
   char completed;             /* true if process has completed */
   char stopped;               /* true if process has stopped */
   int status;                 /* reported status value */
} process;

/* 一个job 代表由管道连接的若干个进程组成的一个作业.  */
typedef struct job
{
   struct job *next;           /* next active job */
   char *command;              /* command line, used for messages */
   process *first_process;     /* list of processes in this job */
   pid_t pgid;                 /* process group ID */
   char notified;              /* true if user told about stopped job */
   struct termios tmodes;      /* saved terminal modes */
   int jstdin, jstdout, jstderr;  /* standard i/o channels */
} job;

/* 活跃的作业组成链表。这是其表头 */
job *first_job = NULL;

pid_t shell_pgid;     
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

/* 保证该shell 在开始工作之前是交互运行的前台作业 */
void init_shell(void)
{
   /* 检查是否交互运行，即判定与STDIN_FILENO相连的是否终端 */
   shell_terminal = STDIN_FILENO;
   shell_is_interactive = isatty(shell_terminal);
   shell_pgid = getpid();

   if (shell_is_interactive) {  /* 是交互运行shell */
      /* 检查是否在前台运行，如果进程组ID不同于控制终端的进程组ID则是在后台运行，
         因而必须发送停止信号，此过程循环直至用户将自己放置于前台 */
      while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
         kill(- shell_pgid, SIGTTIN);
      /* 忽略交互和作业控制信号 */
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGCHLD, SIG_IGN);
      /* 设置shell的进程组 */
      if (setpgid(shell_pgid, shell_pgid) < 0)
         err_exit("Couldn't put the shell in its own process group");
      /* 抢夺控制终端 */
      tcsetpgrp(shell_terminal, shell_pgid);
      /* 保存shell的缺省终端属性以便退出时恢复 */
      tcgetattr(shell_terminal, &shell_tmodes);
   }
}

void launch_process (process *p, pid_t pgid, int infile, 
                     int outfile, int errfile, int foreground)
{
   pid_t pid;

   if (shell_is_interactive) {
      /* 放置该进程至进程组。因为竞争的缘故，子进程和shell二者都必须这样做 */
      pid = getpid();
      if (pgid == 0)          /*  pgid 为0表示这是进程组的第一个进程 */       
         pgid = pid;         /*  使它成为进程组组长 */
      setpgid(pid, pgid);
      /*若是前台进程，给进程组控制终端。*/ 

      if (foreground)
         tcsetpgrp(shell_terminal, pgid);

      /* 设置作业控制信号的句柄回到缺省 */
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      signal(SIGCHLD, SIG_DFL);
   }

   /* 设置新进程的标准I/O通道 */
   if (infile != STDIN_FILENO) {       /* 管道输入情形  */
      dup2(infile, STDIN_FILENO);    /* 复制管道描述字至标准输入描述字 */
      close(infile);                 /* 关闭管道描述字，以下类似 */
   }
   if (outfile != STDOUT_FILENO) {
      dup2(outfile, STDOUT_FILENO);
      close(outfile);
   }
   if (errfile != STDERR_FILENO) {
      dup2(errfile, STDERR_FILENO);
      close(errfile);
   }

   /* 执行新进程 */
   execvp (p->argv[0], p->argv);
   err_exit("execvp");
}

void launch_job(job *j, int foreground)
{
   process *p;
   pid_t pid;
   int mypipe[2], infile, outfile;

   infile = j->jstdin;      /* 第一个进程的标准输入由命令扫描程序指定 */
   for (p = j->first_process; p; p = p->next) {
      /* 有下一个进程，则是用管道连接的。建立管道
         使得这个进程的输出成为下一个进程的输入 */
     if (p->next) {       
        if (pipe(mypipe) < 0) 
           err_exit("pipe");
        outfile = mypipe[1];
     } else
        outfile = j->jstdout;
     /* Fork 子进程 */
     if ((pid = fork()) < 0)    
        err_exit("fork");
     if (pid == 0)          /* 子进程 */
        launch_process(p, j->pgid, infile, outfile, j->jstderr, foreground);
     else{                    /* 父进程 */
        /* 放置该进程至进程组。因为竞争的缘故，子进程和shell二者都必须这样做 */
        p->pid = pid;
        if (shell_is_interactive) {
           if (!j->pgid)
              j->pgid = pid;      /* 记录作业的进程组ID */
           setpgid(pid, j->pgid);
        }
     }
     /* 建立管道之后的清理工作 */
     if (infile != j->jstdin)
        close(infile);
     if (outfile != j->jstdout)
        close(outfile);
     infile = mypipe[0];    /* 下一个进程的标准输入是这个进程的管道输出 */     
   }
   format_job_info(j, "launched");  /* 格式化输出作业状态信息 */
   if (!shell_is_interactive)
      wait_for_job(j);
   else if (foreground)
      put_job_in_foreground(j, 0);
   else
      put_job_in_background(j, 0);
}

void put_job_in_foreground(job *j, int cont)
{
   /*  放置该作业于前台.  */
   tcsetpgrp(shell_terminal, j->pgid);
   /*  如果有必要，向该作业发送一继续信号.  */
   if (cont) {
      tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
      if (kill(- j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
   }
   wait_for_job(j);/*  等待它的报告.  */
   tcsetpgrp (shell_terminal, shell_pgid);   /*  使shell重新回到前台.  */
   /*  恢复shell的终端方式.  */
   tcgetattr(shell_terminal, &j->tmodes);
   tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

/* 放置一个作业至后台。如果cont 参数为真，则向进程组发送一个SIGCONT信号以唤醒它 */
void put_job_in_background(job *j, int cont)
{
   /* 若有必要，向该作业发送继续信号。*/
   if (cont)
      if (kill(-j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
}
