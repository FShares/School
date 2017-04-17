#include "ch12.h"
#include "p12-7.c"   // make_socket()
#define MAXMSG  1024

int main(void)
{
   int sock,size,nbytes;
   struct sockaddr_in name;
   char message[MAXMSG];

   /* �������ݱ��׽��� */
   sock = make_socket(SOCK_DGRAM, 0);

   /* �������ӡϵͳ�����Ķ˿�ֵ */
   size = sizeof(name);
   if (getsockname(sock, (struct sockaddr *)&name, (socklen_t *)&size)) 
      err_exit("getting socket name");
   printf("Socket has port #%d\n", ntohs(name.sin_port));

   while(1){
      /* ���׽��ֶ����� */
      size = sizeof(name);
      nbytes = recvfrom(sock, message, MAXMSG, 0,
                  (struct sockaddr *)&name, (socklen_t *)&size);
      if (nbytes < 0)
         err_exit("recfrom (server)");
      /* ��ӡ���յ�����Ϣ */
      printf("Server got message: %s\n", message);
      /* ����Ϣ���ظ������� */
      nbytes = sendto(sock, message, nbytes, 0,(struct sockaddr *)&name, size);
      if (nbytes < 0)
         err_exit("sendto(server)");
   }
}
