#include "ch13.h"
#define SIZE 10
int a[SIZE],b[SIZE];

void max_fun(int *arg)    /* 求数组最大元素，记录其位置返回 */
{
   int * ap=arg;
   int rv, i, k;
   k=0;
   for (i=1; i<SIZE; i++){
      if (ap[i] > ap[k]) 
         k= i;
   }
   pthread_exit((void *)&ap[k]);   // 递交结果     
}

int main(void)
{
   pthread_t tid1,tid2;    // 线程标识
   int i, rv, **ptr1, **ptr2;
   
   for (i=1; i<SIZE; i++){ // 生成数组元素的数据
      a[i]=rand();
      b[i]=rand();
   }
   /* 创建2个线程执行函数max_fun()分别处理数组a和b */
   rv = pthread_create(&tid1, NULL, (void*(*)())max_fun, a);
   check_error(rv, "pthread_create: tid1");
   rv = pthread_create(&tid2, NULL, (void*(*)())max_fun, b);
   check_error(rv, "pthread_create: tid2");
   /* 等待2个线程结束 */
   pthread_join(tid1, (void **)&ptr1);
   pthread_join(tid2, (void **)&ptr2);
   printf ("thread1's max value is: %d\n", *ptr1);
   printf ("thread2's max value is: %d\n", *ptr2);
   printf ("max value = %d\n", (*ptr1)>(*ptr2)? (*ptr1):(*ptr2));
   exit(0);
}
