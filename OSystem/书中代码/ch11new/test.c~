#include "ch11.h"
int main(void)
{
    int pid, fd[2],len;
    char buffer[PIPE_BUF];
    FILE *stream; 
    if ( pipe(fd) != 0) 
        err_exit("pipe creation failed");
    if ((pid = fork())== 0) { /* 子进程 */
        close(fd[1]);            /* 不使用管道的写端 */
        dup2(fd[0],0);           /* 关闭stdin,重定向管道的输入端至stdin */
        close(fd[0]);            /* 关闭这个不再有用的描述字 */
        /* 用cat过滤输出 */
        if (execl("/bin/cat","cat", NULL/*"-n"*/, NULL) == -1)
            err_exit("Unable to run cat"); 
    } else {                      /* 父进程 */
        close(fd[0]);            /* 不使用管道的输入端 */
        printf("you can type a line and the line will echoed:\n");
        dup2(fd[1],1);           /* 关闭stdout,重定向管道的输出端至stdout */
        close(fd[1]);
        while (gets(buffer) != NULL)
           puts(buffer);         /* 写至管道*/
    }
 } 
