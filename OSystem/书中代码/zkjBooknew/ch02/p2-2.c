#include "ch02.h"
int y_or_n_ques(const char *question)
{
   fputs (question, stdout);     /* ������� */
   while(1){
      int c, answer;
      fputc (' ', stdout);       /* дһ�ո�ֿ�������ش� */
       /* �����е�һ���ַ�.��Ӧ���ǻش��ַ�����Ҳ���ܲ���. */
      c = tolower(fgetc (stdin));
      answer = c;
      while(c != '\n' && c != EOF)   /* ���Դ��е������ַ�. */
          c = fgetc(stdin);
       /* ����ǻش��ַ�����Ӧ�ش�. */
      if (answer == 'y')
          return 1;
      if (answer == 'n')
          return 0;
       /* �ǻش��ַ�������Ҫ��Ϸ��ش�. */
      fputs ("Please answer y or n:", stdout);
   }
}
