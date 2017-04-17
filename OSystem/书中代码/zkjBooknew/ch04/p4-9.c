#include "ch04.h"

char outbuf[100];

int main(void)
{
   int   fdtmp, fdout, length;

   /* ���������ļ���һ����Ϊ�м��ļ���һ����Ϊ����ļ� */
   fdtmp = open("tmpfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   fdout = open("outfile", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
   if ( fdtmp < 0 || fdout < 0) 
      err_exit("ERROR: creat file failed");

   /* ����ɾ���м��ļ� */
  if ( unlink ("tmpfile") < 0 )
      err_exit("unlink call failed");

   /* ���м��ļ�д���ݣ���������ļ��Ѿ�ɾ��������������Ȼ���Զ�д�� */
   length = write(fdtmp, "An example progamm for unlink().", 32);

   /* �����м��ļ� */
   if(lseek(fdtmp, (long)0, SEEK_SET) < 0)
      err_exit("lseek call failed");

   /* �����м��ļ�������ļ� */
   read(fdtmp, outbuf, length);
   write(fdout, outbuf, length);

   close (fdout);
}
