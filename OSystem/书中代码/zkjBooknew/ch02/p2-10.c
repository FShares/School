#include "ch02.h"
int main(void)
{
   FILE *tempfp;
   char tmpname[L_tmpnam],*cp;
   char line[256];
   char *pfx = "XXXXX";
   if ((cp=tmpnam(tmpname))==NULL)  // �鿴tmpnam()���ɵ��ļ���
      printf("a unique name cannot be generate by tmpnam()\n");
   else
      printf("       file name get by tmpnam(): %s\n", cp);
   /* �鿴tempnam()���ɵ��ļ��� */
   cp = tempnam("./", pfx);          
   printf("            by tempnam(\"./\",pfx): %s\n", cp);
   free(cp);
   cp = tempnam("/not_exist_dir/", pfx);
   printf("by tempnam(\"/not_exist_dir\",pfx): %s\n", cp);
   free(cp);
    /* ��tmpfile()����һ����ʱ�ļ� */
   if ((tempfp=tmpfile()) == NULL)
      err_exit("tmpfile error");
   printf("tmpfile() created a temporary file\n");
   /* ����ʱ�ļ�д��һ������,Ȼ����������д����׼���������֤ */
   fputs("One line of output\n", tempfp);
   rewind(tempfp);
   if(fgets(line, sizeof(line), tempfp) == NULL)
      err_exit("fgets error");
   fputs(line,stdout); 
   exit(0);
}
