#include "ch12.h"
#include "p12-7.c"   // make_socket.c", ����12-7
void doit(int);
int main(void)
{
   int server_sockfd, client_sockfd;
   int server_len, client_len;
   struct sockaddr_in client_address;
   server_sockfd = make_socket(SOCK_STREAM, 2003);
   /* �������Ӷ��У������ӽ�����ֹ�ź� */
   listen(server_sockfd, 5);
   signal(SIGCHLD, SIG_IGN);
   while(1) {
      printf("server waiting\n");
      /* �������� */
      client_len = sizeof(client_address);
      client_sockfd = accept(server_sockfd, 
            (struct sockaddr *)&client_address, &client_len);
      /* Ϊ����ͻ�����һ���ӽ��� */
       if(fork() == 0) {             /* ��Ϊ�ӽ��̣����ղ��ش�ͻ�����Ϣ */
         close(server_sockfd);      /* �ӽ��̹ر������׽��� */
         doit(client_sockfd);       /* ����ͻ������� */
         close(client_sockfd);      /* ������Ϲر��׽��� */
         exit(0);                     /* �ӽ�����ֹ */
      } else {
         close(client_sockfd);     /* �����̹رձ����ӵ��׽��� */
      }
   }
}
void doit(client_sockfd)
{
   char buf[255];
   int n;
   /* ���ղ���Ӧ�ͻ�����Ϣ */
   n = read(client_sockfd, buf, sizeof(buf));
   buf[n] = 0;
   sleep(1);
   write(client_sockfd, buf, n);
}
