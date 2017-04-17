#include "ch02.h"
int main (int argc, char *argv[])
{
   int n;
   FILE *from, *to;
   char buf[BUFSIZ] ;
   if (argc != 3) {    /*检查参数。*/
      fprintf(stderr, "Usage : %s from-file to-file\n", *argv) ;
      exit (1);
   }
   if ((from = fopen(argv[1],"r")) == NULL)  /* 为读而打开文件from */
      err_exit (argv[1] ) ; 
	   /* 以添加方式打开文件to. 若此文件不存在，fopen 将创建它。*/
   if ((to=fopen(argv[2], "a")) == NULL)
      err_exit(argv[2] ) ;
	   /* 现在每次可以从文件from读入并写至to. 注意我们写出的字符个数是实际读入
      的字符个数而不总是BUFSIZ字节。*/
   while ((n = fread(buf, sizeof(char),BUFSIZ,from)) > 0)
      fwrite (buf, sizeof(char),n,to) ;
	   /*关闭文件*/
   fclose (from) ;
   fclose (to) ;
   exit (0) ;
}
