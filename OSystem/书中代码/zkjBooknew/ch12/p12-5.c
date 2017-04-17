#include "ch12.h"

int make_un_socket(int type, const char *filename)
{
    struct sockaddr_un name;
    int sock;
    socklen_t size;

    /* 创建套接字 */
    sock = socket(AF_UNIX, type, 0);
    if (sock < 0) 
        err_exit("socket");
    /* 命名套接字 */
    name.sun_family = AF_UNIX;
    strcpy(name.sun_path, filename);
    /* 地址的大小是文件名开始的偏移与其长度之和加1（用于终止的空字节）*/
    size = sizeof(struct sockaddr_un) + 1;
    if (bind (sock, (struct sockaddr *)&name, size) < 0)
        err_exit("bind");
    return sock;
}
