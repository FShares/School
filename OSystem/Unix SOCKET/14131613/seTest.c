#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 2333
main()
{
int i;
struct sockaddr_in server;
bzero(&server, sizeof(server));
printf("sizeof(server):%d ",sizeof(server));
printf("Your server's ip init mem is \n");
for (i=0; i<sizeof(server); i++)
{
    printf(" %02x ", *((unsigned char*)(&server)+i));
}
printf("\n");
server.sin_family=AF_INET;
server.sin_port=htons(PORT);
server.sin_addr.s_addr=inet_addr("192.168.20.96");
printf("Your server's ip sin_family is %d\n", server.sin_family);
printf("Your server's ip is %s, port is %d\n", inet_ntoa(server.sin_addr),ntohs(server.sin_port));
printf("Your server's length is %d\n", sizeof(server));
printf("Your server's ip mem is \n");
for (i =0; i<sizeof(server); i++)
{
printf(" %02x ", *((unsigned char*)(&server)+i));
}
printf("\n");
return ;

}
