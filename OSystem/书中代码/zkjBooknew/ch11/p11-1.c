#include "ch11.h"
int main (void)
{
    pid_t pid;
    int n, mypipe[2];
    char buffer[BUFSIZ+1], some_data[] = "Hello, world!";
    /* 创建管道 */
    if (pipe (mypipe)) 
        err_exit("Pipe failed.\n");
    /* 派生子进程 */ 
    if ((pid = fork())==(pid_t)0) { /* 这是子进程 */
        close(mypipe[1]);     /* 子进程关闭管道输出端 */
        n = read(mypipe[0], buffer, BUFSIZ);
        printf("child %d: read %d bytes: %s\n",getpid(),n,buffer);
    } else {   /* 这是父进程 */
        close(mypipe[0]);    /* 父进程关闭管道输入端 */
        n = write(mypipe[1], some_data, strlen(some_data));
        printf("parent %d: write %d bytes: %s\n", getpid(), n, some_data);
    }
    exit (EXIT_SUCCESS);
}
