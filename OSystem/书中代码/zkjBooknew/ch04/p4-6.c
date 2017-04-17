#include "ch04.h"

int main(int argc, char *argv[])
{
   /* 检查参数合法否 */    
   if (argc != 2){
      printf("usage: a.out <filename>\n");
      exit(1);
   }     
   /* 检查实际用户是否有读权限 */
   if (access(argv[1],R_OK) < 0){              
      printf("access error for %s. ",argv[1]);
      if (errno == EACCES)
         printf("you are not the owner of this file!\n");
   }
   else
      printf("read access OK\n");
   /* 无论是否有实际用户读权限，仍尝试打开该文件 */
   if (open(argv[1], O_RDONLY) < 0)
      printf("open error for %s\n",argv[1]);
   else
      printf("open for reading OK\n");
   exit(0);  
}
