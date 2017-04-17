#include "ch07.h"
void swap_int(int *x, int *y)
{
   /* static */  int swap;
   swap = *x;
   raise(SIGURG);                 /* 模拟在此处到达的信号 */
   *x = *y;
   *y = swap;
}
static void sig_urg(int signo)
{
   int u=30,v=40;
   signal(SIGURG,SIG_IGN);      /* 忽略以后出现的SIGURG信号 */
   swap_int(&u, &v);
   return;
}
int main(void)
{
   int a=1,b=2;
   signal(SIGURG,sig_urg);
   printf("before swap_int: a=%d, b=%d\n",a,b);
   swap_int(&a, &b);
   printf(" after swap_int: a=%d, b=%d\n",a,b);
}
