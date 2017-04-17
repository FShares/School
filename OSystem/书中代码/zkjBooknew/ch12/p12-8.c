#include "ch12.h"
#include "init_sockaddr.c"
int socket_connect(char *hostname, char *serv_port)
{
   int sockfd;
   struct sockaddr_in saddr;
   struct hostent *hp;
   char *host, myname[104];
   /* 初始服务器的IP地址和端口 */
   init_sockaddr(&saddr, hostname, serv_port); 
   /* 创建套接字 */
   if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
      err_exit("socket error");
   /* 建立与服务的连接 */
   if(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
      err_exit("connect error");
   return(sockfd);
}
