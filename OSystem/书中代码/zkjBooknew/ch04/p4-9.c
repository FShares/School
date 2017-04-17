#include "ch04.h"

char outbuf[100];

int main(void)
{
   int   fdtmp, fdout, length;

   /* 创建二个文件，一个作为中间文件，一个作为结果文件 */
   fdtmp = open("tmpfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   fdout = open("outfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   if ( fdtmp < 0 || fdout < 0) 
      err_exit("ERROR: creat file failed");

   /* 立即删除中间文件 */
  if ( unlink ("tmpfile") < 0 )
      err_exit("unlink call failed");

   /* 往中间文件写数据，尽管这个文件已经删除，我们现在仍然可以读写它 */
   length = write(fdtmp, "An example progamm for unlink().", 32);

   /* 反绕中间文件 */
   if(lseek(fdtmp, (long)0, SEEK_SET) < 0)
      err_exit("lseek call failed");

   /* 复制中间文件至结果文件 */
   read(fdtmp, outbuf, length);
   write(fdout, outbuf, length);

   close (fdout);
}
