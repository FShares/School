#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

const int SERV_PORT = 6000;
const int MAXLINE = 2048;

int main(int argc , char **argv)
{
	int sockfd;
	socklen_t len;
	char mesg[MAXLINE];
	struct sockaddr_in servaddr , cliaddr;
	bzero(&servaddr , sizeof(servaddr));
	int num;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	if((sockfd = socket(AF_INET , SOCK_DGRAM , 0)) < 0)
	{
		perror("socket error");
		exit(1);
	}//if

	if(bind(sockfd , (struct sockaddr *)&servaddr , sizeof(servaddr)))
	{
		perror("bind error");
		exit(1);
	}//if

	len = sizeof(cliaddr);
	for( ; ;)
	{
		if((num = recvfrom(sockfd , mesg , MAXLINE , 0 , (struct sockaddr *)&cliaddr , &len))<0)
		{
			perror("recvfrom error");
			exit(1);
		}//if

		printf("You get a message is %s from client.\n It's ip is %s, port is %d.\n",mesg,
			inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port));
		if((num = sendto(sockfd , "Welcome" , 8 , 0 , (struct sockaddr *)&cliaddr , len)) < 0)
		{
			perror("sendto error");
			exit(1);
		}//if

		if(!strcmp(mesg,"bye")) 
			break;
	}//for
	close(sockfd);
}