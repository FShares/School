#include "ch06.h" 

 /* һ�� process ����һ������.  */
typedef struct process
{
   struct process *next;       /* next process in pipeline */
   char **argv;                /* for exec */
   pid_t pid;                  /* process ID */
   char completed;             /* true if process has completed */
   char stopped;               /* true if process has stopped */
   int status;                 /* reported status value */
} process;

/* һ��job �����ɹܵ����ӵ����ɸ�������ɵ�һ����ҵ.  */
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

/* ��Ծ����ҵ��������������ͷ */
job *first_job = NULL;

pid_t shell_pgid;     
struct termios shell_tmodes;
int shell_terminal;
int shell_is_interactive;

/* ��֤��shell �ڿ�ʼ����֮ǰ�ǽ������е�ǰ̨��ҵ */
void init_shell(void)
{
   /* ����Ƿ񽻻����У����ж���STDIN_FILENO�������Ƿ��ն� */
   shell_terminal = STDIN_FILENO;
   shell_is_interactive = isatty(shell_terminal);
   shell_pgid = getpid();

   if (shell_is_interactive) {  /* �ǽ�������shell */
      /* ����Ƿ���ǰ̨���У����������ID��ͬ�ڿ����ն˵Ľ�����ID�����ں�̨���У�
         ������뷢��ֹͣ�źţ��˹���ѭ��ֱ���û����Լ�������ǰ̨ */
      while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
         kill(- shell_pgid, SIGTTIN);
      /* ���Խ�������ҵ�����ź� */
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGCHLD, SIG_IGN);
      /* ����shell�Ľ����� */
      if (setpgid(shell_pgid, shell_pgid) < 0)
         err_exit("Couldn't put the shell in its own process group");
      /* ��������ն� */
      tcsetpgrp(shell_terminal, shell_pgid);
      /* ����shell��ȱʡ�ն������Ա��˳�ʱ�ָ� */
      tcgetattr(shell_terminal, &shell_tmodes);
   }
}

void launch_process (process *p, pid_t pgid, int infile, 
                     int outfile, int errfile, int foreground)
{
   pid_t pid;

   if (shell_is_interactive) {
      /* ���øý����������顣��Ϊ������Ե�ʣ��ӽ��̺�shell���߶����������� */
      pid = getpid();
      if (pgid == 0)          /*  pgid Ϊ0��ʾ���ǽ�����ĵ�һ������ */       
         pgid = pid;         /*  ʹ����Ϊ�������鳤 */
      setpgid(pid, pgid);
      /*����ǰ̨���̣�������������նˡ�*/ 

      if (foreground)
         tcsetpgrp(shell_terminal, pgid);

      /* ������ҵ�����źŵľ���ص�ȱʡ */
      signal(SIGINT, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      signal(SIGTTIN, SIG_DFL);
      signal(SIGTTOU, SIG_DFL);
      signal(SIGCHLD, SIG_DFL);
   }

   /* �����½��̵ı�׼I/Oͨ�� */
   if (infile != STDIN_FILENO) {       /* �ܵ���������  */
      dup2(infile, STDIN_FILENO);    /* ���ƹܵ�����������׼���������� */
      close(infile);                 /* �رչܵ������֣��������� */
   }
   if (outfile != STDOUT_FILENO) {
      dup2(outfile, STDOUT_FILENO);
      close(outfile);
   }
   if (errfile != STDERR_FILENO) {
      dup2(errfile, STDERR_FILENO);
      close(errfile);
   }

   /* ִ���½��� */
   execvp (p->argv[0], p->argv);
   err_exit("execvp");
}

void launch_job(job *j, int foreground)
{
   process *p;
   pid_t pid;
   int mypipe[2], infile, outfile;

   infile = j->jstdin;      /* ��һ�����̵ı�׼����������ɨ�����ָ�� */
   for (p = j->first_process; p; p = p->next) {
      /* ����һ�����̣������ùܵ����ӵġ������ܵ�
         ʹ��������̵������Ϊ��һ�����̵����� */
     if (p->next) {       
        if (pipe(mypipe) < 0) 
           err_exit("pipe");
        outfile = mypipe[1];
     } else
        outfile = j->jstdout;
     /* Fork �ӽ��� */
     if ((pid = fork()) < 0)    
        err_exit("fork");
     if (pid == 0)          /* �ӽ��� */
        launch_process(p, j->pgid, infile, outfile, j->jstderr, foreground);
     else{                    /* ������ */
        /* ���øý����������顣��Ϊ������Ե�ʣ��ӽ��̺�shell���߶����������� */
        p->pid = pid;
        if (shell_is_interactive) {
           if (!j->pgid)
              j->pgid = pid;      /* ��¼��ҵ�Ľ�����ID */
           setpgid(pid, j->pgid);
        }
     }
     /* �����ܵ�֮��������� */
     if (infile != j->jstdin)
        close(infile);
     if (outfile != j->jstdout)
        close(outfile);
     infile = mypipe[0];    /* ��һ�����̵ı�׼������������̵Ĺܵ���� */     
   }
   format_job_info(j, "launched");  /* ��ʽ�������ҵ״̬��Ϣ */
   if (!shell_is_interactive)
      wait_for_job(j);
   else if (foreground)
      put_job_in_foreground(j, 0);
   else
      put_job_in_background(j, 0);
}

void put_job_in_foreground(job *j, int cont)
{
   /*  ���ø���ҵ��ǰ̨.  */
   tcsetpgrp(shell_terminal, j->pgid);
   /*  ����б�Ҫ�������ҵ����һ�����ź�.  */
   if (cont) {
      tcsetattr(shell_terminal, TCSADRAIN, &j->tmodes);
      if (kill(- j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
   }
   wait_for_job(j);/*  �ȴ����ı���.  */
   tcsetpgrp (shell_terminal, shell_pgid);   /*  ʹshell���»ص�ǰ̨.  */
   /*  �ָ�shell���ն˷�ʽ.  */
   tcgetattr(shell_terminal, &j->tmodes);
   tcsetattr(shell_terminal, TCSADRAIN, &shell_tmodes);
}

/* ����һ����ҵ����̨�����cont ����Ϊ�棬��������鷢��һ��SIGCONT�ź��Ի����� */
void put_job_in_background(job *j, int cont)
{
   /* ���б�Ҫ�������ҵ���ͼ����źš�*/
   if (cont)
      if (kill(-j->pgid, SIGCONT) < 0)
         perror("kill (SIGCONT)");
}
