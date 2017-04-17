#include "ch04.h"

int main(int argc, char*argv[])
{  
   long int length;
   int fd;
   char *cp;
   
   if (argc != 3){   /* ����������ȷ�� */
      printf("usage: a.out <filename> <file size>\n");
      exit(1);
   }

   /* ��ȡ���������ļ� */
   length = strtol(argv[2], &cp, 10); 
   if (cp==argv[2]) {  /* �ڶ����������� */
      printf("usage: a.out <filename> <file size> and "
             "<file size> must be a integer\n");
      exit(1);
   }

   if ((fd = open(argv[1],O_RDWR)) < 0)
      err_exit("open() call failed");

   /* ���ڶ�����ָ���ֽڽض��ļ� */
   printf ("truncate %s to %d characaters\n", argv[1], length);
   if ( ftruncate(fd, length) < 0 ) 
      err_exit("truncate() call failed");
   printf ("truncate() call successful\n");

   lseek(fd,(long)0, SEEK_END); /* ��λ���ļ�β */
   write(fd, "@T" ,2);          /* д��β����ʶ */

   close(fd);
}
