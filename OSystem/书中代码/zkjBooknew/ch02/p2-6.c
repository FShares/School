#include "ch02.h"
#include "y_or_n_ques.c"
char buf[132];
int main(int argc, char *argv[])
{
   FILE *fd;
   fpos_t pos;
   if (!y_or_n_ques("Should we use append mode?")) {
     if ((fd = fopen("test_file","w+")) == NULL)  /* 以写方式打开文件  */
        err_exit("fopen faild");
   } else {
     if ((fd = fopen("test_file","a+")) == NULL)  /* 以添加方式打开文件  */
        err_exit("fopen faild");
   }
   fputs("0123456789ABCDEFGHIJ ",fd);    /* 写入一行数据 */
	   /* 查看当前文件尾位置 */
   fseek(fd,0,SEEK_END);
   fgetpos(fd,&pos);
   printf("current file position is %ld\n",pos);
   fseek(fd,30,SEEK_END);   /* 定位至文件尾之后30字节，并查看当前文件尾位置  */
   fgetpos(fd,&pos);	
   printf("Now we call fseek(fd,30,SEEK_END); "
            "current file position is %ld\n",pos);
   fputs("abcdefg",fd); 	 /* 写入数据 */
   printf("Now we write 7 bytes \"%s\"\n","abcdefg");
   fgetpos(fd,&pos);        /* 查看当前文件尾位置 */
   printf("current file position is %ld\n",pos);
   fclose(fd);
}
