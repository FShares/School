#include "ch13.h"
#define NUM_THREADS 4 
#define VECL 4*10000000
double a[VECL], b[VECL], sum;
struct args {         // dotsum使用的数据
   pthread_t tid;       // 线程ID
   int l_sum;           // 局部点积
   int index;               // 从0开始的线程编号
} tharg[NUM_THREADS];     // 每个线程对应一个元素
void *dotsum(void *arg)   // 求部分点积的线程开始函数
{
   struct args *ap = (struct args *)arg;
   int  i, start, end;
   double l_sum = 0.0;                           // 局部点积
   start = ap->index * (VECL/NUM_THREADS);   // 向量开始点 
   end   = start + (VECL/NUM_THREADS);        // 向量结束点 
   printf("thread %i do from index %d to %d\n",ap->index, start,end-1);
   for (i = start; i < end; i++) 
      l_sum += (a[i]*b[i]);
   ap->l_sum = l_sum;                           // 保存计算结果 
   return;
}
int main(void)
{
   int  i;
   assert(VECL%4==0);                  // 只有满足此条件程序才正确 
   for (i=0; i<VECL; i++)
      a[i]=b[i]=1.0;
   for(i=1; i<NUM_THREADS; i++) {  // 创建NUM_THREADS-1个线程并发执行dotsum()函数 
      tharg[i].index = i;
      pthread_create(&tharg[i].tid, NULL, dotsum, (void *)&tharg[i]);
   }
   tharg[0].index = 0;
   dotsum((void *)&tharg[0]);      /* 主线程参与计算 */
   for(i=1; i<NUM_THREADS; i++)   /* 等待其它线程完成计算 */
      pthread_join(tharg[i].tid, (void **)NULL);
   /* 累加每个线程的部分和并输出结果 */
   sum=0.0;
   for (i=0; i<NUM_THREADS; i++)
      sum += tharg[i].l_sum;
   printf ("Sum =  %lf \n", sum);
   pthread_exit(NULL);
}
