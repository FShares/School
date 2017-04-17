#include "ch04.h"
int main(int argc, char *argv[])
{
   char *ptr = malloc(PATH_MAX + 1);
   if (argc != 2){
      printf ("Usage: a.out <pathname>\n");
      exit (EXIT_FAILURE);
   }
   if (getwd(ptr)==NULL)        // 查看当前工作目录
      err_exit("getwd failed");
   printf("Current work directory is :%s\n", ptr);
   if (chdir (argv[1]) < 0)    //改变工作目录
      err_exit("chdir failed");
   if (getwd(ptr)==NULL)       //查看新的工作目录
      err_exit("getwd failed");
   printf("CWD = %s\n",ptr);
   free(ptr);
}
