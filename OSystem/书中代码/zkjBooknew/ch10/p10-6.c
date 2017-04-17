#include "ch10.h"

int input_timeout(int filedes, unsigned int seconds)
{
    fd_set set;
    struct timeval timeout;
    int n;
    char buf[1024];

    FD_ZERO(&set);             /* 初始文件描述字集合 */
    FD_SET(filedes, &set);
    timeout.tv_sec = seconds;  /* 初始timeout数据结构 */
    timeout.tv_usec = 0;

    /* select时间到期返回0；输入就绪返回1；出现错误返回-1 */
again:
    if ((n = select(FD_SETSIZE, &set, NULL, NULL, &timeout)) < 0) { //出现错误
        if (errno = EINTR) 
            goto again;
    }
    else if (n > 0) {   //输入就绪
        n = read(filedes,buf,sizeof(buf));
        printf("read data:  %s\n",buf);
    }
    else  //时间到期
        printf("tiomeout for select\n");
    return n;
}

int main (void)
{
    fprintf(stderr, "select returned %d.\n",input_timeout(STDIN_FILENO, 5));
    return 0;
}
