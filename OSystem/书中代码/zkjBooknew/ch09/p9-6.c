#include "ch09.h"
int main(void)
{
   int  n1, n2, fd;
   if((fd=open("/dev/ttyS0", O_RDWR|O_NOCTTY|O_NONBLOCK))== -1){
      fprintf(stderr, "Open port: Unable to open, %s\n",strerror(errno));
      exit(EXIT_FAILURE);
   }
   write(fd, "Example of line control functions ", 34);
   tcdrain(fd);             /* 等待输出队列中的数据全部送出 */
   tcflow(fd, TCOOFF);      /* 悬挂输出传送 */
   n1 = write(fd, "this line will be thrown over\n", 30);
   tcflush(fd, TCOFLUSH);   /* 清除输出队列 */ 
   n2 = write(fd, "this line will not be thrown over\n", 34);
   tcflow(fd, TCOON);       /* 恢复输出传送 */
   write(fd,"restart the output\n",19);
   exit(EXIT_SUCCESS);
}
