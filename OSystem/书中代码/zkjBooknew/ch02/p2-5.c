#include "ch02.h"
int main (int argc, char *argv[])
{
   int n;
   FILE *from, *to;
   char buf[BUFSIZ] ;
   if (argc != 3) {    /*��������*/
      fprintf(stderr, "Usage : %s from-file to-file\n", *argv) ;
      exit (1);
   }
   if ((from = fopen(argv[1],"r")) == NULL)  /* Ϊ�������ļ�from */
      err_exit (argv[1] ) ; 
	   /* ����ӷ�ʽ���ļ�to. �����ļ������ڣ�fopen ����������*/
   if ((to=fopen(argv[2], "a")) == NULL)
      err_exit(argv[2] ) ;
	   /* ����ÿ�ο��Դ��ļ�from���벢д��to. ע������д�����ַ�������ʵ�ʶ���
      ���ַ�������������BUFSIZ�ֽڡ�*/
   while ((n = fread(buf, sizeof(char),BUFSIZ,from)) > 0)
      fwrite (buf, sizeof(char),n,to) ;
	   /*�ر��ļ�*/
   fclose (from) ;
   fclose (to) ;
   exit (0) ;
}
