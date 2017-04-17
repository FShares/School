#include "ch14.h"
pthread_key_t key;
pthread_once_t key_once= PTHREAD_ONCE_INIT;
/* 创建key，通过pthread_once保证只创建一次 */
void key_once_initial(void)
{
int rv;
   printf("I am in key_once_initial. My TID is %lx\n", pthread_self());
   rv = pthread_key_create(&key, NULL);
   check_error(rv,"Create key");
}

/* 线程开始函数，。。。*/
void *thread_routine(void *arg)
{
   int rv;
   pthread_t tid;
   tid = pthread_self();
   printf("%s call pthread_once, TID=%lx\n",arg,tid);
   rv = pthread_once(&key_once, key_once_initial); /*创建key一次且仅一次 */
   check_error(rv, "Once init");
   // ... 使用线程专有数据键和完成线程其他工作的代码
   return NULL;
}
int main(int argc, char*arg[])
{
   pthread_t thread1, thread2;
   int rv;
   rv = pthread_create(&thread1, NULL, thread_routine, "thread 1");
   check_error(rv, "Create thread 1");
   rv = pthread_create(&thread2, NULL, thread_routine, "thread 2");
   check_error(rv, "Create thread 2");
   pthread_exit(NULL);
}

