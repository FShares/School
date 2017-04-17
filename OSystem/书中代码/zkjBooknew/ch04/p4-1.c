#include "ch04.h"
void * xmalloc(int);     /* ����5-6 */
read_specs(char *filename)
{
   int desc;
   struct stat statbuf;
   char *buffer;
   register char *p;
   desc = open(filename, O_RDONLY, 0);    /* ���ļ�����ȡ�ļ���Ϣ */
   if (desc < 0)
     err_exit(filename);
   if (stat(filename,&statbuf) < 0)
     err_exit(filename);
   /* Ϊbuffer�����СΪst_size�Ŀռ� */
   buffer = xmalloc ((unsigned)statbuf.st_size + 1); 
   read (desc,buffer,(unsigned)statbuf.st_size);     /* �������ļ�������buffer */
   buffer[statbuf.st_size] = 0;
   close (desc);
   /* ���������ļ���... */
}
