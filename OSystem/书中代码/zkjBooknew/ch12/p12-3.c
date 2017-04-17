#include "ch12.h"
int main(void)
{
   int    stayopen = 1;
   struct servent *sp;
   setservent(stayopen);    /* 打开服务数据库，准备扫描 */
   while (1) {                /* 逐项扫描登记项 */
      sp = getservent();
      if (sp != (struct servent *)0)
         printf( "server name=%12s, port=%6d, proto=%4s\n", sp->s_name,
                   ntohs(sp->s_port), sp->s_proto);
      else
         break;
   }
   endservent();    /* 关闭服务数据库 */
   /* 专门查看telnet服务的端口号 */
   sp = getservbyname ("telnet", "tcp");
   if (sp != (struct servent *)0) 
      printf( "telnet's port is %d\n", ntohs (sp->s_port));
   else
      printf("ERROR: getservbyname call failed\n");
   return 0;
}
