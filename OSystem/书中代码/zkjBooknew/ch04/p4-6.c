#include "ch04.h"

int main(int argc, char *argv[])
{
   /* �������Ϸ��� */    
   if (argc != 2){
      printf("usage: a.out <filename>\n");
      exit(1);
   }     
   /* ���ʵ���û��Ƿ��ж�Ȩ�� */
   if (access(argv[1],R_OK) < 0){              
      printf("access error for %s. ",argv[1]);
      if (errno == EACCES)
         printf("you are not the owner of this file!\n");
   }
   else
      printf("read access OK\n");
   /* �����Ƿ���ʵ���û���Ȩ�ޣ��Գ��Դ򿪸��ļ� */
   if (open(argv[1], O_RDONLY) < 0)
      printf("open error for %s\n",argv[1]);
   else
      printf("open for reading OK\n");
   exit(0);  
}
