#include "ch14.h"
int count;
int i=-1;             // 取消点标志
volatile int val=0;   // volatile修饰以防编译器对它进行优化

void *thread_routine(void *arg)   // 线程开始函数 
{
   int state = PTHREAD_CANCEL_DISABLE;
   int oldstate, j;
   for (count=1;;count++) {
      for(j=0;j<1000;j++)   // 模拟工作
         val=(val*j)/count;
      if (count%1024 ==0){
         i=1;
         pthread_testcancel(); // // 每隔2048个迭代回应一次取消请求
      } else if ((count-100)%2048 == 0) {
         /* 进入不可取消工作区 */
         pthread_setcancelstate(state, &oldstate); // 不允许被取消
         for(j=0;j<1000000;j++)
            val=(val*j)/count;
         pthread_setcancelstate(oldstate, &state);  // 恢复以前的可取消状态
         i=0;      
         pthread_testcancel(); // 之后及时回应可能出现的悬挂取消请求
      } 
   }
}
int main(void)
{
   pthread_t tid;
   int rv;
   void * result;
   rv=pthread_create(&tid, NULL, thread_routine, NULL);
   check_error(rv,"Create thread");
   sleep(3);
   rv=pthread_cancel(tid);              // 向线程发出取消请求
   check_error(rv, "cancel thread");
   rv=pthread_join(tid, &result);
   if (result == PTHREAD_CANCELED)
      printf("thread %lx was canceled at itertion %d,i=%d\n", tid,count,i);
   else 
      printf("Thread %lx was not canceled. count=%d,i=%d\n",tid, count, i);
   return 0;
}
