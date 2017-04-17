#include "ch12.h"
int main(int argc, char *argv[])
{
   char *host, **names, **addrs, myname[256];
   struct hostent *hostinfo;
   /* 设置主机为命令行参数指定的名字或程序运行所在机器的名字 */
   if(argc > 1) 
  host = argv[1];
   else {
      gethostname(myname, 255);
      host = myname;
   }   
   hostinfo = gethostbyname(host);       /* 获取主机地址信息 */
   if(!hostinfo) {
      fprintf(stderr, "cannot get info for host: %s\n", host);
      exit(1);
   }
   /* 报告它的正式名和别名 */
   printf("results for host %s:\n", host);
   printf("Official name: %s\n", hostinfo->h_name);
   printf("\t Aliases:");
   names = hostinfo->h_aliases;
   while(*names) {
      printf(" %s\n", *names);
      names++;
   }
    /* 报告IP地址 */
   addrs = hostinfo->h_addr_list;
   while(*addrs) {
      printf("\taddress:%s\n",inet_ntoa(*(struct in_addr*)*addrs));
       addrs++;
   }
   exit(0);
}
