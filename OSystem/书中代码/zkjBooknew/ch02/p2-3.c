#include "ch02.h"
#define BUF_SIZE 8

int main(void)
{
   FILE *fd;
   int fgets_yes;
   struct iobuf {
       char buf[BUF_SIZE];
       char others[BUF_SIZE];
   }buffer;
  
   memset(&buffer,'\0',sizeof(struct iobuf)); 
   do {
       /* 请用户选择使用fgets()还是gets() */
       fgets_yes = y_or_n_ques("Should we read by fgets()?");
       fprintf(stdout,"please enter a line\n");
       if(fgets_yes) {   /* 用fgets读输入数据 */
          fgets(buffer.buf, BUF_SIZE, stdin);
          fprintf(stdout,"fgets() get string \"%s\"\n",buffer.buf);
          while(buffer.buf[strlen(buffer.buf)-1] != '\n'){ /* 一行未读完，继续读 */
             fgets(buffer.buf, BUF_SIZE , stdin); 
             fprintf(stdout,"fgets() get string \"%s\"\n",buffer.buf);
          }
       } else {   /* 用gets读输入数据 */
          gets(buffer.buf);
          fprintf(stdout,"gets() get string \"%s\"\n",buffer.buf);
       }
       /* 查看溢出情况 */
       fprintf(stdout,"buffer.others is \"%s\"\n",buffer.others);
   } while (y_or_n_ques("continue?"));
   exit(0);
}

