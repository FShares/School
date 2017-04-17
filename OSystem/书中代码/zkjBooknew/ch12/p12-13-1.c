#include "ch12.h"
#include "p12-7.c"   // make_socket.c", 程序12-7
void doit(int);
int main(void)
{
   int server_sockfd, client_sockfd;
   int server_len, client_len;
   struct sockaddr_in client_address;
   server_sockfd = make_socket(SOCK_STREAM, 2003);
   /* 创建连接队列，忽略子进程终止信号 */
   listen(server_sockfd, 5);
   signal(SIGCHLD, SIG_IGN);
   while(1) {
      printf("server waiting\n");
      /* 接收连接 */
      client_len = sizeof(client_address);
      client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);
      /* 为这个客户创建一个子进程 */
       if(fork() == 0) {             /* 若为子进程，接收并回答客户的消息 */
         close(server_sockfd);      /* 子进程关闭侦听套接字 */
         doit(client_sockfd);       /* 处理客户的请求 */
         close(client_sockfd);      /* 处理完毕关闭套接字 */
         exit(0);                     /* 子进程终止 */
      } else {
         close(client_sockfd);     /* 父进程关闭被连接的套接字 */
      }
   }
}
void doit(client_sockfd)
{
   char buf[255];
   int n;
   /* 接收并回应客户的消息 */
   n = read(client_sockfd, buf, sizeof(buf));
   buf[n] = 0;
   sleep(1);
   write(client_sockfd, buf, n);
}
