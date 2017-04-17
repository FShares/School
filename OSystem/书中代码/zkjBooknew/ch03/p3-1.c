#include "ch03.h"
int main (int argc, char **argv)
{
   int n, from, to;
   char buf[1024] ;
   if (argc != 3) {      /* ������������*/
      printf("Usage : %s from-file to-file\n", argv[0]);
      exit (1);
   }
   if ((from = open (argv[1],O_RDONLY)) < 0)  /* Ϊ�������ļ�from */
      err_exit (argv[1] ); 
  /* ����ӷ�ʽ���ļ�to. ���ļ������ڣ�open() ���Է�ʽ644��-rw-r--r--)��������*/
   if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0)
      err_exit (argv[2] );
   /* ���ļ�from�����ݲ�д��to.ÿ��д�����ַ�������ÿ�ζ�����ַ����� */
   while ((n = read(from, buf, sizeof(buf))) > 0)
       write (to, buf, n) ;
   close(from) ;     /* �ر��ļ� */
   close(to) ;
}
