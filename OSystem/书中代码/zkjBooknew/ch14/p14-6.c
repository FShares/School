//#include "ch14.h"
struct sched_thread {
   int num;
   int policy;
   int priority;
   void * (*thread_func)();
};

pthread_t create_exlicit_sched_threads(struct sched_thread *arg)
{
   pthread_t tid;
   pthread_attr_t attr;
   struct sched_param param;
   int rv, scope;

   assert(arg->policy==SCHED_FIFO||arg->policy==SCHED_RR);
   /* 初始化线程属性对象 */
   rv = pthread_attr_init(&attr);
   check_error(rv, "attr init");
   /* 设置线程属性对象中的线程调度继承属性为非继承 */
   rv = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
   check_error(rv, "attr_setinheritsched");
   /* 设置其竞争范围为系统范围 */
   rv = pthread_attr_getscope(&attr, &scope);
   check_error(rv, "attr_ getscope");
   if (scope != PTHREAD_SCOPE_SYSTEM){
      rv = pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
      check_error(rv, "attr_ setscope");
   }
   /* 创建一个指定调度属性的线程 */
   rv = pthread_attr_setschedpolicy(&attr, arg->policy);    // 设置调度策略
   check_error(rv, "create_exlicit_sched_thread:setschedpolicy");
   param.sched_priority = arg->priority;                   // 设置调度优先级
   rv = pthread_attr_setschedparam(&attr, &param);      
   check_error(rv, "create_exlicit_sched_thread:setschedparam");
   rv = pthread_create(&tid, &attr, arg->thread_func, (void *)arg->num);
   check_error(rv, "create thread 1");
   /* 销毁线程属性对象 */
   rv = pthread_attr_destroy(&attr);
   check_error(rv, "attr destroy");
   return tid;
}
