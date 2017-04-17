#include "ch13.h"
#include <sys/mman.h>
#define STACK_GROWS_DOWN
#undef  STACK_GROWS_UP
void Hello(void)
{
   int array[512];
   printf("Hello, &array=%d\n", &array);
   Hello(); 
}
/* 申请线程栈空间并创建栈溢出保护区。栈地址对齐在页边界上，栈大小扩充为页的倍数 */
void *thread_stack_alloc(size_t size)   
{
   int pagesize;
   void *mem, *guard_addr, *stack_addr;
   if (size < PTHREAD_STACK_MIN){
     fprintf(stderr, " thread_stack_alloc: SIZE less than PTHREAD_STACK_MIN\n");
     exit(1);
   }
   /* 计算栈大小为页的整倍数 */
   pagesize = sysconf(_SC_PAGESIZE);
   if(size % pagesize != 0)   
      size = ((size + pagesize) / pagesize) * pagesize;
   /* 申请对齐在页边界上的存储空间，其中包含作为栈溢出区的额外一页 */
   mem = (void *)valloc(size + pagesize);
   /* 创建溢出保护区 */
#ifdef STACK_GROWS_UP
   guard_addr = mem + size;
   stack_addr = mem;
#else
   guard_addr = mem;
   stack_addr = mem + pagesize;
#endif
   if (mprotect(guard_addr, pagesize, PROT_NONE))
      err_exit("mprotect");
   printf("stack area=(%d,%d)\n", stack_addr, stack_addr+size-1);
   printf("gaurded area=(%d,%d)\n", guard_addr, guard_addr+pagesize-1);
   return stack_addr;
}
int main (void)
{
   pthread_t thread;
   int rv;
   pthread_attr_t attr;
   size_t stacksize, guardsize;
   char *stackaddr;
   pthread_attr_init(&attr);      /* 初始化线程属性对象*/
   /* 申请用作线程栈的空间 */
   stackaddr = (void *)thread_stack_alloc(PTHREAD_STACK_MIN); 
   /* 设置线程属性对象中的栈地址和大小 */
   rv = pthread_attr_setstack(&attr, stackaddr, PTHREAD_STACK_MIN); 
   check_error(rv, "pthread_setstack()");
   /* 查看栈属性值 */   
   pthread_attr_getstack(&attr, (void *)&stackaddr, &stacksize);
   pthread_attr_getguardsize(&attr, &guardsize);
   printf("stack attributes: stackaddr=%d, stacksize=%d, guardsize=%d\n", 
           stackaddr, stacksize, guardsize);
   /* 创建线程 */
   rv = pthread_create(&thread, &attr, (void *(*)())Hello, (void *)NULL);
   check_error(rv, "pthread_create()");
   pthread_attr_destroy(&attr);   /* 及时销毁线程属性对象，避免再次使用 */
   check_error(rv, "pthread_attr_destroy()");
   /* ... 后继程序代码 ... */
   pthread_exit(NULL);
}
