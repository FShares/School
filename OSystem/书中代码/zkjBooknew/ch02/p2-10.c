#include "ch02.h"
int main(void)
{
   FILE *tempfp;
   char tmpname[L_tmpnam],*cp;
   char line[256];
   char *pfx = "XXXXX";
   if ((cp=tmpnam(tmpname))==NULL)  // 查看tmpnam()生成的文件名
      printf("a unique name cannot be generate by tmpnam()\n");
   else
      printf("       file name get by tmpnam(): %s\n", cp);
   /* 查看tempnam()生成的文件名 */
   cp = tempnam("./", pfx);          
   printf("            by tempnam(\"./\",pfx): %s\n", cp);
   free(cp);
   cp = tempnam("/not_exist_dir/", pfx);
   printf("by tempnam(\"/not_exist_dir\",pfx): %s\n", cp);
   free(cp);
    /* 用tmpfile()创建一个临时文件 */
   if ((tempfp=tmpfile()) == NULL)
      err_exit("tmpfile error");
   printf("tmpfile() created a temporary file\n");
   /* 往临时文件写入一行数据,然后将它读出并写至标准输出进行验证 */
   fputs("One line of output\n", tempfp);
   rewind(tempfp);
   if(fgets(line, sizeof(line), tempfp) == NULL)
      err_exit("fgets error");
   fputs(line,stdout); 
   exit(0);
}
