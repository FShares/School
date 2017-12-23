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
	/* 
	 bzero初始化 sockadd_in(/usr/include/netinet/in.h)
	 结构体server（16个byte）置0
	*/
	bzero(&server, sizeof(server));

	/*
	server: P13-14
	struct sockaddr_in {
		short int sin_family;			// 2 byte
		unsigned short int sin_port;    // 2 byte
		struct in_addr sin_addr;        // 4 byte
		unsigned char sin_zer[8];       // 8 byte
	} // 16 byte
	+----------------------------------------------------------------------------+
	|sin_family(2 byte)	|sin_port(2 byte)	|sin_addr(4 byte)	|sin_zero(8 byte)|
	|0 					|0 					|0 					|0               |
	+----------------------------------------------------------------------------+
	*/
	printf("Your server's ip init mem is \n");
	for (i=0; i<sizeof(server); i++){
	    printf(" %02x ", *((unsigned char*)(&server)+i));       /*v*/
	}//以十六进制占两位字符输出server值为0(全为0)。
	/*
	其中网际套接字地址结构体中共包含5个成员，sin_len是长度成员，占一个字节，
	存储套接字地址结构的长度，但不是所有系统都支持，
	有了它可以简化变长套接字地址结构的处理。
	一般情况下不需要设置它和检查它，除非涉及到路由套接字，
	本处并没有涉及到路由套接字所以只有32个零，否则可能是34个零。
	*/
	printf("\n");
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);
	server.sin_addr.s_addr=inet_addr("192.168.20.96");
	printf("Your server's ip sin_family is %d\n", server.sin_family);
	/* server结构体中sin_family为2(Internet地址族,IPv4默认是AF_INET)  */
	printf("Your server's ip is %s, port is %d\n", inet_ntoa(server.sin_addr),ntohs(server.sin_port));
	/* server结构体成员sin_addr.s_addr(存放网络字节序32位ip地址),
	成员sin_port(网络字节序2 byte)  sin_addr 和 sin_port 
	分别封装在包的 IP 和 UDP 层(必需使用网络字节序）
	>>1.inet_ntoa函数将网际套接字结构中存储的32位的网络字节序的二进制IP地址转换成
	人们通用的点分十进制的IP地址并输出为192.168.20.96
	>>2.PORT在开头被声明为2333，在server.sin_port=htons(PORT)语句中被转换成网络字节序给sin_port
	  ntohs函数的作用是将16位的短整型数从网络字节序转换成主机字节序并以整形形式输出为 2333
	*/
	printf("Your server's length is %d\n", sizeof(server));
	/*
	server 的大小
	sockaddr_in结构体中包含5个成员，其中sin_len是长度成员，
	存储套接字地址结构的长度，但不是所有系统都支持，
	一般情况下不需要设置它和检查它，除非涉及到路由套接字。 
	本程序并没有设置这个成员，所以只有16个字节。 
	*/
	printf("Your server's ip mem is \n");
	for (i =0; i<sizeof(server); i++){
		printf(" %02x ", *((unsigned char*)(&server)+i));
	}
	/* 
	+-----------------------------------------------------------------------------------------+
	|                                      server                                             |
	|sin_family(2 byte)	|sin_port(2 byte)	|sin_addr(4 byte)	      |sin_zero(8 byte)       |
	|02  00 (十六进制)  |09 1d (十六进制)   |c0 a8 14 60 (十六进制)   |00 00 00 00 00 00 00 00|
	|(小端字节序)	    |2333  (十进制)	    |192.168.20.96 (十进制)   |(十六进制)             |
	+-----------------------------------------------------------------------------------------+
	sin_family：以小端方式存储，其值占两个字节，所以空出的部分补零
	*/
	printf("\n");
	return;
}
