#include "ch04.h"
void * xmalloc(int);     /* 程序5-6 */
read_specs(char *filename)
{
   int desc;
   struct stat statbuf;
   char *buffer;
   register char *p;
   desc = open(filename, O_RDONLY, 0);    /* 打开文件并获取文件信息 */
   if (desc < 0)
     err_exit(filename);
   if (stat(filename,&statbuf) < 0)
     err_exit(filename);
   /* 为buffer分配大小为st_size的空间 */
   buffer = xmalloc ((unsigned)statbuf.st_size + 1); 
   read (desc,buffer,(unsigned)statbuf.st_size);     /* 读整个文件内容至buffer */
   buffer[statbuf.st_size] = 0;
   close (desc);
   /* 处理读入的文件，... */
}
