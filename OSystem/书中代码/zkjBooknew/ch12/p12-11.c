#include "ch12.h"
#include "p12-7.c"  // make_socket()
#define LISTENQ  5
#define MAXLINE  512
int main(int argc, char **argv)
{
   int listenfd,connfd;
   socklen_t len;
   struct sockaddr_in servaddr,cliaddr;
   char buff[MAXLINE];
   time_t ticks;
   /* 创建并命名套接，5013为服务端口 */
   listenfd = make_socket(SOCK_STREAM, 5013);  
   listen(listenfd, LISTENQ);    /* 创建侦听队列 */
   /* 连接处理 */
   for(; ;){
     len = sizeof(cliaddr);
      /* 接收连接 */
     connfd=accept(listenfd, (struct sockaddr *)&cliaddr, &len);
      /* 打印出连接客户的IP地址 */
     printf("connect from %s,port %d\n", 
                    inet_ntoa((struct in_addr)cliaddr.sin_addr),
                    ntohs(cliaddr.sin_port));
      /* 向客户报告时间 */
     ticks = time(NULL);
     sprintf(buff,"%.24s\r\n",ctime(&ticks));
     write(connfd,buff,strlen(buff));
     close(connfd);        /* 关闭连接套接字 */
   }
}
