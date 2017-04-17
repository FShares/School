#include "ch14.h"
pthread_key_t key1, key2;
/* ʹ���߳�ר�����ݵĹ������� */
void do_work(void)
{
   int num;
   char *vp;
   num = (int)pthread_getspecific(key1); /* ����߳�ר�����ݣ�����һ������ */
   vp = (char *)pthread_getspecific(key2);  /* ����߳�ר�����ݣ�����һ��ָ�� */
   sprintf(vp,"\tThread %d is at work now, key2's value:%x ", num, vp);
}
/* �߳̿�ʼ���������������߳�ר�����ݼ�ֵ֮ */
void start_func(int thread_num)
{
   char *buf, *vp;
   pthread_setspecific(key1, (void *)thread_num);
   buf = (char *)malloc(100);
   pthread_setspecific(key2, (void *)buf);
   do_work();
   vp = (char *)pthread_getspecific(key2);
   printf("Thread %d's thread specific data is :\n %s\n", thread_num, vp);
   if (thread_num !=0 ) // ��ʼ�̷߳��أ������߳���ֹ
     pthread_exit(NULL);
}
/* �߳�ר�����ݼ������������������������߳���ֹʱ�ͷŷ���Ĵ洢�ռ� */
void destructor(void *value)
{
   free(value);
   printf("memory %x released by destructor\n",value);
}
int main(int argc,char *argv[])
{
   int rv;
   pthread_t tid;
   /* �����߳�ר�����ݼ�key1��key2 */
   rv = pthread_key_create(&key1, NULL);
   check_error(rv, "Create key1");
   rv = pthread_key_create(&key2, destructor);
   check_error(rv, "Create key2");
   /* ����һ���߳���star_func�Ĺ���,���̱߳��Ϊ1 */
   rv = pthread_create(&tid, NULL, (void *(*)())start_func, (void *)1);
   check_error(rv, "Thread create");
   /* �Լ�Ҳ���빤�������̱߳��Ϊ0 */
   start_func(0);
   /* �ȴ��߳���ֹ */
   rv = pthread_join(tid, NULL);
   check_error(rv, "Thread join ");
   rv = pthread_key_delete(key1);
   check_error(rv, "key1 delete");
   pthread_exit(NULL);
}

