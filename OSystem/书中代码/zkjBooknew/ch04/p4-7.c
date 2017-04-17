#include "ch04.h"

int main(int argc, char*argv[])
{  
   long int length;
   int fd;
   char *cp;
   
   if (argc != 3){   /* 检查参数的正确性 */
      printf("usage: a.out <filename> <file size>\n");
      exit(1);
   }

   /* 读取参数并打开文件 */
   length = strtol(argv[2], &cp, 10); 
   if (cp==argv[2]) {  /* 第二参数非数字 */
      printf("usage: a.out <filename> <file size> and "
             "<file size> must be a integer\n");
      exit(1);
   }

   if ((fd = open(argv[1],O_RDWR)) < 0)
      err_exit("open() call failed");

   /* 按第二参数指定字节截断文件 */
   printf ("truncate %s to %d characaters\n", argv[1], length);
   if ( ftruncate(fd, length) < 0 ) 
      err_exit("truncate() call failed");
   printf ("truncate() call successful\n");

   lseek(fd,(long)0, SEEK_END); /* 定位至文件尾 */
   write(fd, "@T" ,2);          /* 写入尾部标识 */

   close(fd);
}
