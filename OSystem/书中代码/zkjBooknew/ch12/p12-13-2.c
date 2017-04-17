#include "ch12.h"
#include "p12-8.c"   // socket_connect.c, 程序12-8
int main(int argc, char **argv)
{
    int connfd, n, result;
    char buf[256];
    connfd = socket_connect(NULL, "2003");    /* 与服务建立连接 */
    write(connfd, argv[1], sizeof(argv[1]));  /* 向服务发送数据 */
    n = read(connfd, buf, sizeof(buf));        /* 读服务的回送数据 */
    buf[n] = 0;  /* 终止符 */
    printf("string from server = %s\n", buf);
    close(connfd);
    exit(0);
}
