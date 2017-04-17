#include "ch12.h"
#define DATA1   "Fine,thanks."
#define DATA2   "Hello,how are you?"
int main(void)
{
    int sockets[2], child;
    char buf[1024];
    /* 创建套接字偶对 */
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockets) < 0) 
        err_exit("socketpair error");
    /* 创建子进程*/
    if ((child = fork()) == -1) 
        err_exit("fork error ");
    if (child != 0) {       /* 这是父进程 */
        close(sockets[0]);  /* 关闭子进程的套接字 */
        /* 读来自子进程的消息 */
        if (read(sockets[1], buf, sizeof(buf)) < 0) 
            err_exit("reading socket error");
        printf("parent %d received request: %s\n", getpid(), buf);
        /* 向子进程写消息 */
        if (write(sockets[1], DATA1, sizeof(DATA1)) < 0) 
            err_exit("writing socket error");
        close(sockets[1]);    /* 通信结束 */
    } else {     /* 这是子进程 */
        close(sockets[1]);     /* 关闭父进程的套接字端 */
        /* 发送消息给父进程 */
        if (write(sockets[0], DATA2, sizeof(DATA2)) < 0) 
            err_exit("writing socket error");
        /* 读来自父进程的消息 */
        if (read(sockets[0], buf, sizeof(buf)) < 0)
            err_exit("reading socket error");
        printf("child process %d received answer: %s\n", getpid(),buf);
        close(sockets[0]);     /* 通信结束 */
    }
}
