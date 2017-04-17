#include "ch12.h"
int main(void)
{
   int    stayopen = 1;
   struct servent *sp;
   setservent(stayopen);    /* �򿪷������ݿ⣬׼��ɨ�� */
   while (1) {                /* ����ɨ��Ǽ��� */
      sp = getservent();
      if (sp != (struct servent *)0)
         printf( "server name=%12s, port=%6d, proto=%4s\n", sp->s_name,
                   ntohs(sp->s_port), sp->s_proto);
      else
         break;
   }
   endservent();    /* �رշ������ݿ� */
   /* ר�Ų鿴telnet����Ķ˿ں� */
   sp = getservbyname ("telnet", "tcp");
   if (sp != (struct servent *)0) 
      printf( "telnet's port is %d\n", ntohs (sp->s_port));
   else
      printf("ERROR: getservbyname call failed\n");
   return 0;
}
