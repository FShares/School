#include "ch12.h"
#include "p12-6.c"   //init_sockaddr()
#define MAXMSG 512
int main(int argc, char **argv) 
{ 
   ...
   /* 设置套接字接收超时选项 */
   timev.tv_sec = 5;
   timev.tv_usec = 0;
   setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timev, sizeof(timev));
   while(1){
      ...
       /* 接收并显示服务返回的回答,若超时或出错，终止执行 */
      if ((n = recvfrom(sock,rcvmsg, MAXMSG,0,NULL,NULL)) < 0){
         if(errno == EWOULDBLOCK) 
            fprintf(stderr,”socket timeout\n”);
         err_exit("(client) receive error ");         
      }
      rcvmsg[n] = 0;
      printf(“client received message: %s”,rcvmsg);
   }
   ...
}

