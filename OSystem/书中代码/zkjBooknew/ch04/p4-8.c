#include "ch04.h"

int main(int argc, char *argv[])
{
   int i;
   struct  stat statbuf;
   struct utimbuf times;

   if (argc != 2) {
      printf("Usage: a.out filename\n");
      exit(1);
   }
   if (stat(argv[1],&statbuf) < 0)       /* 获得文件的当前时间 */
      err_exit(argv[1]);
   if (open(argv[1],O_RDWR|O_TRUNC) < 0)      /* 截断文件 */
      err_exit(argv[1]);
   printf("%s is truncated now.\n", argv[1] );
   times.actime = statbuf.st_atime;          /* 恢复文件时间至原时间 */
   times.modtime = statbuf.st_mtime;   
   if (utime(argv[1], &times) == 0)            
      printf ("utime() successful\n");
   else
      printf ("ERROR: utime() failed. %s\n",strerror(errno));
   exit(0);
}
