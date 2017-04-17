#include "ch02.h"
#include "y_or_n_ques.c"
char buf[132];
int main(int argc, char *argv[])
{
   FILE *fd;
   fpos_t pos;
   if (!y_or_n_ques("Should we use append mode?")) {
     if ((fd = fopen("test_file","w+")) == NULL)  /* ��д��ʽ���ļ�  */
        err_exit("fopen faild");
   } else {
     if ((fd = fopen("test_file","a+")) == NULL)  /* ����ӷ�ʽ���ļ�  */
        err_exit("fopen faild");
   }
   fputs("0123456789ABCDEFGHIJ ",fd);    /* д��һ������ */
	   /* �鿴��ǰ�ļ�βλ�� */
   fseek(fd,0,SEEK_END);
   fgetpos(fd,&pos);
   printf("current file position is %ld\n",pos);
   fseek(fd,30,SEEK_END);   /* ��λ���ļ�β֮��30�ֽڣ����鿴��ǰ�ļ�βλ��  */
   fgetpos(fd,&pos);	
   printf("Now we call fseek(fd,30,SEEK_END); "
            "current file position is %ld\n",pos);
   fputs("abcdefg",fd); 	 /* д������ */
   printf("Now we write 7 bytes \"%s\"\n","abcdefg");
   fgetpos(fd,&pos);        /* �鿴��ǰ�ļ�βλ�� */
   printf("current file position is %ld\n",pos);
   fclose(fd);
}
