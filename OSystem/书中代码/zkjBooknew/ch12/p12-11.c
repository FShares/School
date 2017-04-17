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
   /* �����������׽ӣ�5013Ϊ����˿� */
   listenfd = make_socket(SOCK_STREAM, 5013);  
   listen(listenfd, LISTENQ);    /* ������������ */
   /* ���Ӵ��� */
   for(; ;){
     len = sizeof(cliaddr);
      /* �������� */
     connfd=accept(listenfd, (struct sockaddr *)&cliaddr, &len);
      /* ��ӡ�����ӿͻ���IP��ַ */
     printf("connect from %s,port %d\n", 
                    inet_ntoa((struct in_addr)cliaddr.sin_addr),
                    ntohs(cliaddr.sin_port));
      /* ��ͻ�����ʱ�� */
     ticks = time(NULL);
     sprintf(buff,"%.24s\r\n",ctime(&ticks));
     write(connfd,buff,strlen(buff));
     close(connfd);        /* �ر������׽��� */
   }
}
