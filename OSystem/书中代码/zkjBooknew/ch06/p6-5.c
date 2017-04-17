#include "ch06.h"
#include "p6-3.c" //pr_exit()

/*  parse--�ֽ�buf�е�����Ϊ�����Ĳ���  */
void parse(char *buf, char *args[])
{
   int i=0;
   while (*buf != '\0') {
      /* �ÿ��ַ�'\0'����հ��ַ�ʹ��ǰһ�����Կ��ַ�����  */       
      args[i++]=buf;
      while ((*buf!=' ')&&(*buf!='\t')&&(*buf!='\n')) buf++;
      while ((*buf==' ')||(*buf=='\t'||(*buf=='\n'))) *buf++ = '\0';
   }
   args[i]='\0';
}

/*  execute--����һ�ӽ���ִ�д˳���  */
void execute(char *args[])
{
   int pid, status;
   /*  ����һ�ӽ���  */
   if ((pid=fork()) <0) 
      err_exit("fork");
   /*  �ӽ���ִ��if�ڵĴ���  */
   if (pid==0) {
      execvp(*args,args);
      err_exit("execvp");
   } 
   /*  �����̵ȴ��ӽ������  */
   waitpid(pid, &status, 0);
   pr_exit(status,pid);
}
int main(void)
{
   char buf[1024];
   char *args[64], *cp;

   for (;;) {
     printf("Command: ");   // ������ʾ��
     cp = fgets (buf, sizeof(buf), stdin);    //��������
     if (cp == (char *)NULL || *cp == '\n'){  // ���б�ʾ�˳�
        printf("quit\n");
        exit(EXIT_SUCCESS);
     }
     /*  �ֽ��ַ���Ϊ����  */
     parse(buf, args);
     /*  ִ������  */
     execute(args);
   }
}

