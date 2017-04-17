#include "ch05.h"
#include "xmalloc.c"

int main(int argc,char *argv[])
{
   char *value;  
   if(argc==1||argc>3) {   /* 检查调用参数是否正确*/
      fprintf(stderr, "Usage: <environ var> [<value>]\n");
      exit(1);
   }
  
   value = getenv(argv[1]); /* 取环境变量之值 */
   if(value)
      printf("Variable %s = %s\n",argv[1],value);
   else
      printf("Variable %s undefined\n",argv[1]);
   if(argc==3){  /* 三个参数的情形  */
      char *string = xmalloc(strlen(argv[1])+strlen(argv[2])+2);
      strcpy(string,argv[1]);  // 形成"name=value"  
      strcat(string,"=");
      strcat(string,argv[2]);
      printf("calling putenv with: %s\n",string);
      if(putenv(string)!=0){  /* 设置新环境变量  */
         free(string);
         err_exit("putenv error");
      }
      value = getenv(argv[1]); /* 核实该变量的新值  */
      printf("New value of %s = %s\n",argv[1],value);
   }
   exit(0);
}
