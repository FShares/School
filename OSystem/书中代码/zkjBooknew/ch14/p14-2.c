#include "ch14.h"
pthread_key_t key1, key2;
/* 使用线程专有数据的工作函数 */
void do_work(void)
{
   int num;
   char *vp;
   num = (int)pthread_getspecific(key1); /* 获得线程专有数据，这是一个常数 */
   vp = (char *)pthread_getspecific(key2);  /* 获得线程专有数据，这是一个指针 */
   sprintf(vp,"\tThread %d is at work now, key2's value:%x ", num, vp);
}
/* 线程开始函数，负责设置线程专有数据键之值 */
void start_func(int thread_num)
{
   char *buf, *vp;
   pthread_setspecific(key1, (void *)thread_num);
   buf = (char *)malloc(100);
   pthread_setspecific(key2, (void *)buf);
   do_work();
   vp = (char *)pthread_getspecific(key2);
   printf("Thread %d's thread specific data is :\n %s\n", thread_num, vp);
   if (thread_num !=0 ) // 初始线程返回，其它线程终止
     pthread_exit(NULL);
}
/* 线程专有数据键相连的析构函数，负责在线程终止时释放分配的存储空间 */
void destructor(void *value)
{
   free(value);
   printf("memory %x released by destructor\n",value);
}
int main(int argc,char *argv[])
{
   int rv;
   pthread_t tid;
   /* 创建线程专有数据键key1和key2 */
   rv = pthread_key_create(&key1, NULL);
   check_error(rv, "Create key1");
   rv = pthread_key_create(&key2, destructor);
   check_error(rv, "Create key2");
   /* 创建一个线程做star_func的工作,其线程编号为1 */
   rv = pthread_create(&tid, NULL, (void *(*)())start_func, (void *)1);
   check_error(rv, "Thread create");
   /* 自己也参与工作，其线程编号为0 */
   start_func(0);
   /* 等待线程终止 */
   rv = pthread_join(tid, NULL);
   check_error(rv, "Thread join ");
   rv = pthread_key_delete(key1);
   check_error(rv, "key1 delete");
   pthread_exit(NULL);
}

