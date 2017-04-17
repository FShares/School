#include "ch03.h"
int main (int argc, char **argv)
{
   int n, from, to;
   char buf[1024] ;
   if (argc != 3) {      /* 检查参数个数。*/
      printf("Usage : %s from-file to-file\n", argv[0]);
      exit (1);
   }
   if ((from = open (argv[1],O_RDONLY)) < 0)  /* 为读而打开文件from */
      err_exit (argv[1] ); 
  /* 以添加方式打开文件to. 若文件不存在，open() 将以方式644（-rw-r--r--)创建它。*/
   if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0)
      err_exit (argv[2] );
   /* 从文件from读数据并写至to.每次写出的字符个数是每次读入的字符个数 */
   while ((n = read(from, buf, sizeof(buf))) > 0)
       write (to, buf, n) ;
   close(from) ;     /* 关闭文件 */
   close(to) ;
}
