#include "ch12.h"
#include "p12-6.c"   //init_sockaddr()
#define MAXMSG 512
int main(int argc, char **argv) 
{ 
   int sock,n; 
   struct sockaddr_in name; 
   struct hostent *hp;
   char sndmsg[MAXMSG],rcvmsg[MAXMSG];

   /* �������ĺϷ��� */
   if (argc < 3) {
     fprintf(stderr, "Usage: a.out <hostname> <port>\n");
     exit(1);
   }

   /* �������ݱ��׽��� */ 
   if ((sock = socket(AF_INET, SOCK_DGRAM, 0))< 0) 
      err_exit("opening datagram socket"); 

   /* �γɷ���Ŀ�ĵ��׽���ȱʡ��ַ */ 
   init_sockaddr(&name, argv[1], argv[2]);
   connect(sock, (struct sockaddr *)&name, sizeof(name)); 

   while(1) {
      printf("Please enter any string(Quit by RETURN key):");
      fgets(sndmsg,MAXMSG,stdin);
      if (sndmsg[0]=='\n')
         break;
      /* ���ʹ��ն˶������Ϣ */
      if (write (sock, sndmsg, sizeof(sndmsg)) < 0) 
         err_exit("(client) sending error");
      /* ���ղ���ʾ���񷵻صĻش� */
      if ((n = read(sock,rcvmsg, MAXMSG)) < 0)
         err_exit("(client) receive error ");
      rcvmsg[n] = 0;
      printf("I received echo: %s",rcvmsg);
   }

   close(sock);
   exit(0); 
}
